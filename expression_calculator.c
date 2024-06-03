//write a program to convert infix to postfix.
#include <stdio.h>
#include <string.h>
#include "list.h"

void printHelp() {
    printf("Help: This program converts to calculate simple infix expression.\n");
    printf("Usage: ./cal [options] [expression]\n");
    printf("Options:\n");
    printf("  -h, --help     Display this help message.\n");
    printf("  -v, --verbose  Display Display the infix to Postfix Version.\n");
    printf("  -V, --version  Display version information.\n");
}


void printVersion() {
    printf("Version: v1.0.0\n");
}

void main(int argc, char *argv[]) {
    cstack *st1 = NULL;
    int isVer = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printHelp();
            return;
        }
        if (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0) {
            printVersion();
            return;
        }

        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0) {
            isVer = 1;
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