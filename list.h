#include "util.h"

typedef struct List{
    double data;
    char op;
    struct List *next;
}list;


void push(list **l1, char op, double number){
    list *new_node = (list*)malloc(sizeof(list));
    new_node->data = number;
    new_node->op = op;
    if(!*l1){
        new_node->next = *l1;
        *l1 = new_node;
        return;
    }
    new_node->next = NULL;
    list *temp = *l1;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = new_node;
}

void displayExp(list *head) {
    while (head != NULL) {
        if(head->op == '1'){
            long num = head->data;
            if(num < head->data){
                printf("%.2f ",head->data);
            }else{
                printf("%d ",num);
            }
        }else{
            printf("%c ", head->op);
        }
        head = head->next;
    }
    printf("\n");
}

typedef struct charStack{
    char data;
    struct charStack *next;
}cstack;

void push_char_top(cstack **st, char data){
    cstack *new_node = (cstack*)malloc(sizeof(cstack));
    new_node->data = data;
    new_node->next = *st;
    *st = new_node;
}

char pop(cstack **st){
    cstack *temp = *st;
    *st = (*st)->next;
    char data = temp->data;
    free(temp);
    return data;
}

void push_char(cstack **st, char data){
    cstack *new_node = (cstack*)malloc(sizeof(cstack));
    new_node->data = data;
    if(!*st){
        new_node->next = *st;
        *st = new_node;
        return;
    }
    new_node->next = NULL;
    cstack *temp = *st;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = new_node;
}

void scan_char(cstack **head){
    char c;
    while(1){
        scanf("%c",&c);
        if(c == 32){
            continue;
        }
        push_char(head,c);
        if(c == 10)break;
    }
}

void displayc(cstack *head) {
    while (head->next != NULL) {
        printf("%c", head->data);
        head = head->next;
    }
    // printf("\n");
}

double toNumber(cstack *st){
    double num = 0;
    int isNeg = 0;
    int isPoint = 0;
    int point = 0;
    if(st->data == '-'){
        isNeg = 1;
        st = st->next;
    }
    while(st->next != NULL){
        if(st->data == 46){
            isPoint = 1;
            st = st->next;
            break;
        }
        int n = st->data-48;
        num = (num*10) + n;
        st = st->next;
    }
    int len = 1;
    if(isPoint){
        while(st->next != NULL){
            if(st->data == 46){
                printf("multiple '.' found. \nProgram Crashed.");
                exit(0);
            }
            int n = st->data-48;
            point = (point*10)+n;
            len *= 10;
            st = st->next;
        }
    }
    num = (num*len+point)/len;
    if(isNeg){
        return num*-1;
    }
    return num;
}

list* charToList(cstack *st){
    cstack* number = NULL, *prev = NULL;
    list *l1 = NULL;
    int isNeg = 0;
    char c;
    while(st != NULL){
        c = st->data;
        if(isNumber(c)){
            push_char(&number,c);
        }
        if(isOperator(c) || isBrace(c)){
            if(number != NULL){
                push_char(&number,c);
                push(&l1,'1',toNumber(number));
                number = NULL;
            }
            if(c == '-'){
                if(prev == NULL ||  isOperator(prev->data) || prev->data == '('){
                    push_char(&number,c);
                }else{
                    push(&l1,c,0);
                }
            }else{
                push(&l1,c,0);
            }
        }
        prev = st;
        st = st->next;
    }
    if(number != NULL){
        push_char(&number,c);
        push(&l1,'1',toNumber(number));
        number = NULL;
    }
    return l1;
}

void infixToPostfix(list **l){
    list *l1 = *l, *postlist = NULL;
    cstack *oplist = NULL;
    while(l1 != NULL){
        if(l1->op == '1'){
            push(&postlist,'1',l1->data);
        }else{
            if(oplist == NULL || l1->op == 40 || opPref(l1->op) > opPref(oplist->data)){
                push_char_top(&oplist,l1->op);
            }else{
                if(l1->op == ')'){
                    while(oplist != NULL && oplist->data != '('){
                        push(&postlist,pop(&oplist),0);
                    }
                    if(oplist != NULL && oplist->data == '('){
                        char garbg = pop(&oplist);
                    }
                }else{
                    while(oplist != NULL && opPref(l1->op) <= opPref(oplist->data)){

                        push(&postlist,pop(&oplist),0);
                    }
                    push_char_top(&oplist,l1->op);
                }
            }
        }
        l1 = l1->next;
    }
    while(oplist != NULL){
        push(&postlist,pop(&oplist),0);
    }
    *l = postlist;
}


double evaluate_postfix(list *l1) {
    // Consider using a stack for storing numbers instead of list nodes
    double stack[100];  // Adjust MAX_STACK_SIZE as needed
    int top = -1;
    double num1, num2, result;
    while (l1 != NULL) {  // Iterate through all elements
        if (l1->op != '1') {  // Assuming '1' indicates an operator
            num2 = stack[top--];
            num1 = stack[top--];
            result = calculate(num1, l1->op, num2);  // Assuming calculate handles errors
            stack[++top] = result;
        } else {
            stack[++top] = l1->data;  // Push number onto stack
        }
        l1 = l1->next;
    }

    // Return the final result from the stack
    return stack[top];
}

int chekcexp(char a,char b, char c){
    if(b == ' '){
        if(isOperator(c)){
            if(c != '-'){
                return 0;
            }
        }
        return 1;
    }
    if(isNumber(b)){
        if(c == '('){
            return 0;
        }
        return 1;
    }
    if(isOperator(b)){
        if(isOperator(c)){
            if(c != '-'){
                return 0;
            }else{
                if(isOperator(a) || isBrace(a)){
                    return 0;
                }
            }
        }
        if(c == ')' || c == ' '){
            return 0;
        }
        return 1;
    }
    if(b == ')'){
        if(isOperator(a) || isNumber(c)){
            return 0;
        }
    }
    if(b == '('){
        if((!isNumber(c) && c != '-') || isNumber(a)){
            return 0;
        }
    }
    if(!(isNumber(b) || isOperator(b) || isBrace(b))){
        printf("Invalid Char( %c ).\n",b);
        return 0;
    }
    return 1;
}

int checkBrace(cstack *temp){
    char stack[10];
    int top = -1;
    while(temp->next != NULL){
        if(temp->data == '('){
            stack[++top] = temp->data;
        }else{
            if(stack[top--] != '('){
                return 1;
            }
        }
        temp = temp->next;
    }
    if(top != -1){
        return 1;
    }
    return 0;
}

int checkerror(cstack *head){
    cstack *temp = NULL;
    char prev = ' ';
    char p = ' ';
    char next = ' ';
    while(head->next != NULL){
        prev = p;
        p = next;
        next = head->data;
        if(!chekcexp(prev, p, next)){
            printf("Expression Error.\n");
            printf("take a look at this part %c %c %c",prev,p,next);
            exit(0);
        }
        if(isBrace(head->data)){
            push_char(&temp, head->data);
        }
        head = head->next;
    }
    prev = p;
    p = next;
    next = ' ';
    if(!chekcexp(prev, p, next)){
        printf("Expression Error.\n");
        printf("take a look at the end %c %c %c",prev,p,next);
        exit(0);
    }

    push_char(&temp,'\n');
    if(checkBrace(temp)){
        displayc(temp);
        printf("Brackets not Matched Properly");
        exit(0);
    }
    return 0;
}