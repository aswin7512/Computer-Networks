#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;
int tempCount = 1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        if (isalnum(c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();
            pop();
        }
        else {
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(c))
                postfix[j++] = pop();

            push(c);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

void generateTAC(char postfix[]) {
    char operandStack[100][20];
    int opTop = -1;
    int i;

    char op1[20], op2[20], result[20];

    for (i = 0; postfix[i] != '\0'; i++) {

        if (isalnum(postfix[i])) {
            sprintf(operandStack[++opTop], "%c", postfix[i]);
        }
        else {
            strcpy(op2, operandStack[opTop--]);
            strcpy(op1, operandStack[opTop--]);

            sprintf(result, "t%d", tempCount++);

            printf("%s = %s %c %s\n",
                   result, op1, postfix[i], op2);

            strcpy(operandStack[++opTop], result);
        }
    }
}

int main() {
    char expression[100];
    char postfix[100];

    printf("Enter expression: ");
    scanf("%s", expression);

    infixToPostfix(expression, postfix);

    printf("\nThree Address Code:\n");
    generateTAC(postfix);

    return 0;
}

