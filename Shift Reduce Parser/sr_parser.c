#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

char input[MAX];
int ip = 0;

void push(char c) {
    stack[++top] = c;
}

char pop(void) {
    if (top < 0) return '\0';
    return stack[top--];
}

void print_config(const char *action) {
    int i;
    printf("%-25s", action);
    for (i = 0; i <= top; i++) putchar(stack[i]);
    printf("\t\t");
    printf("%s\n", input + ip);
}

int reduce(void) {
    if (top >= 0 && stack[top] == 'i') {
        pop();
        push('E');
        print_config("Reduce: id -> E");
        return 1;
    }

    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        print_config("Reduce: E*E -> E");
        return 1;
    }

    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        print_config("Reduce: E+E -> E");
        return 1;
    }

    if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        pop(); pop(); pop();
        push('E');
        print_config("Reduce: (E) -> E");
        return 1;
    }

    return 0;
}

int main(void) {
    printf("Shift-Reduce Parser\n");
    printf("Enter input string (e.g. i+i*i  or  (i+i)*i): ");

    if (fgets(input, MAX, stdin) == NULL) {
        printf("No input read.\n");
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';

    printf("\n%-25s%-12s%s\n", "ACTION", "STACK", "INPUT");
    printf("--------------------------------------------------------\n");

    int len = (int)strlen(input);

    while (1) {

        char next = (ip < len) ? input[ip] : '\0';

        if (top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E' && next == '*') {
        } else if (reduce()) {
            continue;
        }

        if (ip >= len) {
            break;
        }

        char c = input[ip++];
        if (c == 'i' || c == '+' || c == '*' || c == '(' || c == ')') {
            push(c);
            print_config("Shift");
        } else {
            printf("\nError: invalid symbol '%c' in input.\n", c);
            return 1;
        }
    }

    if (top == 0 && stack[0] == 'E' && ip >= len) {
        printf("\nResult: Input string is ACCEPTED by the grammar.\n");
    } else {
        printf("\nResult: Input string is REJECTED (stack = ");
        for (int i = 0; i <= top; i++) putchar(stack[i]);
        printf(").\n");
    }

    return 0;
}
