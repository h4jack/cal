//write a program to convert infix to postfix.
#include <stdio.h>
#include <string.h>
#include "list.h"

void main(int argc, char *argv[]) {
    cstack *st1 = NULL;
    int isVer = 0;
    if (argc > 1) {
        int errorindex = 0;
        if(argv[1][0] == '-' && (argv[1][1] == 'v' || argv[1][1] == 'V')){
            if(strlen(argv[1]) == 2){
                isVer = 1;
            }
        }
        for (int i = 1+isVer; i < argc; i++) {
            int len = strlen(argv[i]);
            for (int j = 0; j < len; j++) {
                push_char(&st1,argv[i][j]);
            }
        }
        push_char(&st1,'\n');
        // displayc(st1);
    }else{
        printf("Enter the Infix Expression(e.g. 10*(-13+17)/1.5-17 ): ");
        scan_char(&st1);
    }
    //error check.
    checkerror(st1);

    list *l1 = charToList(st1);
    if(isVer){
        printf("Your Infix Expression is:\n");
        displayExp(l1);
    }
    infixToPostfix(&l1);
    if(isVer){
        printf("The Postfix Version of the Expression is:\n");
        displayExp(l1);
    }
    double result = evaluate_postfix(l1);
    displayc(st1);
    printf(" : %.3lf\n",result);
}

/*
0-9 = 48-57
( 40
) 41
42 *
43 +
45 -
46 .
47 /
37 %
94 ^
*/