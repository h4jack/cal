# Infix to Postfix Expression Converter

This C program converts an infix expression to a postfix expression, which is useful for evaluating mathematical expressions in computer programs. This README aims to explain how the code works and how you can use it.

## How It Works

The conversion from infix to postfix expression is achieved using a stack data structure. Here's a step-by-step explanation of the process:

1. **Tokenization:** The input infix expression is split into individual tokens, which can be operands, operators, or parentheses.

2. **Conversion Algorithm:** The conversion algorithm iterates over each token in the infix expression and performs the following actions:
   - If the token is an operand, it is immediately added to the output postfix expression.
   - If the token is an operator:
     - If the stack is empty or the token has higher precedence than the top operator on the stack, the token is pushed onto the stack.
     - Otherwise, operators with equal or higher precedence are popped from the stack and added to the output until a lower precedence operator is encountered or the stack is empty. Then, the token is pushed onto the stack.
   - If the token is a left parenthesis, it is pushed onto the stack.
   - If the token is a right parenthesis, operators are popped from the stack and added to the output until a left parenthesis is encountered. The left parenthesis is then discarded.

3. **Finalization:** After processing all tokens, any remaining operators on the stack are popped and added to the output.

4. **Output:** The resulting postfix expression is obtained by concatenating all tokens in the output.

## Code Explanation

The C code provided consists of functions to perform infix to postfix conversion and evaluate the resulting postfix expression. Here's a brief overview of each function:

- **`push`:** Adds a new node to the end of a linked list.
```c
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
```
#### Example:
    list *l1 = NULL;
    push(&l1, '*', 10);
    push(&l1, '+', 5);

- **`push_char_top`:** Pushes a character onto the top of a character stack.
```c
void push_char_top(cstack **st, char data){
    cstack *new_node = (cstack*)malloc(sizeof(cstack));
    new_node->data = data;
    new_node->next = *st;
    *st = new_node;
}
```
#### Expmple:
    cstack *st1 = NULL;
    push_char_top(&st1, '+');
    push_char_top(&st1, '-');

- **`pop`:** Removes and returns the top element from a character stack.
```c
char pop(cstack **st){
    cstack *temp = *st;
    *st = (*st)->next;
    char data = temp->data;
    free(temp);
    return data;
}
```
#### Example:
    cstack *st1 = NULL;
    push_char_top(&st1, '*');
    char op = pop(&st1); // op will be '*'

- **`push_char`:** Pushes a character onto the end of a character stack.
```c
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
```
#### Example:
    cstack *st1 = NULL;
    push_char(&st1, '/');
    push_char(&st1, '+');

- **`scan_char`:** Scans input characters until a newline character is encountered and pushes them onto a character stack.
```c
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
```
#### Example:
    cstack *st1 = NULL;
    printf("Enter the infix expression: ");
    scan_char(&st1);

- **`displaylist`:** Displays the contents of a linked list.
```c
void displaylist(list *head) {
    while (head != NULL) {
        if(head->op == '1'){
            printf("%.2lf",head->data);
        }else{
            printf("%c", head->op);
        }
        head = head->next;
        if(head != NULL){
            printf(" , ");
        }
    }
    printf("\n");
}
```
#### Example:
    list *l1 = NULL;
    push(&l1, '*', 10);
    push(&l1, '+', 5);
    displaylist(l1); // Output: 10 , + , 5

- **`displayExp`:** Displays the contents of a linked list, converting numeric values to their appropriate format.
```c
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
```
#### Example:
    list *l1 = NULL;
    push(&l1, '*', 10);
    push(&l1, '+', 5);
    displayExp(l1); // Output: 10.00 + 5.00

- **`displayc`:** Displays the contents of a character stack.
```c
void displayc(cstack *head) {
    while (head->next != NULL) {
        printf("%c", head->data);
        head = head->next;
    }
    // printf("\n");
}
```
#### Example:
    cstack *st1 = NULL;
    push_char(&st1, '/');
    push_char(&st1, '+');
    displayc(st1); // Output: /+


- **`isNumber`, `isOperator`, `isBrace`, `opPref`:** Helper functions to identify whether a character is a number, parenthesis, operator, or its precedence.

**`isNumber:`**
```c
int isNumber(char c){
    return (c >= 48 && c <= 57) || c == 46;
}
```

**`isOperator:`**
```c
int isOperator(char c){
    return (c == 45 || c == 43 || c == 42 || c == 47 || c == 37 || c == 94);
}
```

**`isBrace:`**
```c
int isBrace(char c){
    return (c == 40 || c == 41);
}
```
**`opPref:`**
```c
int opPref(char c){
    switch(c){
        case 94:
            return 6;
        case 47:
            return 4;
        case 37:
        case 42:
            return 3;
        case 43:
        case 45:
            return 1;
        case 40:
        case 41:
            return 0;
        default:
            exit(0);
    }
}
```
- **`toNumber`:** Converts a character stack representing a number to its corresponding numeric value.
```c
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
```
#### Example:
```c
cstack *st1 = NULL;
push_char(&st1, '1');
push_char(&st1, '0');
double num = toNumber(st1); // num will be 10.0
```

- **`charToList`:** Converts a character stack representing an infix expression to a linked list of individual tokens.
```c
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
```
#### Example:
```c
cstack *st1 = NULL;
push_char(&st1, '1');
push_char(&st1, '0');
push_char(&st1, '*');
push_char(&st1, '(');
push_char(&st1, '1');
push_char(&st1, '3');
push_char(&st1, '-');
push_char(&st1, '1');
push_char(&st1, '7');
push_char(&st1, ')');
list *l1 = charToList(st1); // Resulting list: 10.00 * ( 13 - 17 )
```

- **`infixToPostfix`:** Converts an infix expression represented as a linked list to a postfix expression.
```c
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
```
#### Example:
```c
list *l1 = NULL;
push(&l1, '*', 10);
push(&l1, '+', 5);
infixToPostfix(&l1); // Resulting postfix expression: 10.00 5.00 +
```

- **`calculate`:** Performs arithmetic operations based on the given operator and operands.
```c
double calculate(double num1, char op, double num2){
    switch(op){
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '%':
            return fmod(num1,num2);
        case '^':
            return pow(num1,num2);
        default:
            printf("Invalid Operator.\n");
            return 0;
    }
    return 0;
}
```
- **`evaluate_postfix`:** Evaluates a postfix expression represented as a linked list and returns the result.
```c
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

```
#### Example:
```c
list *l1 = NULL;
push(&l1, '*', 10);
push(&l1, '+', 5);
double result = evaluate_postfix(l1); // Result will be the evaluated expression
```


## Usage

To use the code, follow these steps:

1. Compile the C program using a C compiler (e.g., GCC).
2. Run the compiled executable.
3. Enter the infix expression when prompted or provide it as command-line arguments.
4. The program will output the postfix expression and the result of evaluating the expression.

```plaintext
$ gcc infix_to_postfix.c -o infix_to_postfix
$ ./infix_to_postfix
Enter the Infix Expression: 10*(-13+17)/1.5-17
The Postfix Version of the Expression is: 10 13 - 17 + * 1.5 / 17 -
Result: <result>
