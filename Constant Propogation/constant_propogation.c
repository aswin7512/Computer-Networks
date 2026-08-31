#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Statement {
    char lhs[20];
    char op1[20];
    char op2[20];
    char op;
};

int isConstant(char *str) {
    int i = 0;

    if (str[0] == '-')
        i = 1;

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int main() {
    int n, i, value;
    struct Statement s[20];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements in the form: x = y + z\n");
    printf("For constant assignment use: x = 10\n\n");

    for (i = 0; i < n; i++) {
        char input[50];

        printf("Statement %d: ", i + 1);
        scanf(" %[^\n]", input);

        char *eq = strchr(input, '=');

        if (eq == NULL) {
            printf("Invalid statement!\n");
            i--;
            continue;
        }

        *eq = '\0';

        strcpy(s[i].lhs, input);

        char rhs[30];
        strcpy(rhs, eq + 1);

        char *p = strchr(rhs, '+');
        s[i].op = '+';

        if (!p) {
            p = strchr(rhs, '-');
            s[i].op = '-';
        }

        if (!p) {
            p = strchr(rhs, '*');
            s[i].op = '*';
        }

        if (!p) {
            p = strchr(rhs, '/');
            s[i].op = '/';
        }

        if (p) {
            *p = '\0';
            strcpy(s[i].op1, rhs);
            strcpy(s[i].op2, p + 1);
        } else {
            strcpy(s[i].op1, rhs);
            strcpy(s[i].op2, "");
            s[i].op = '=';
        }

        // Remove spaces
        for (int j = 0; s[i].lhs[j]; j++)
            if (s[i].lhs[j] == ' ')
                s[i].lhs[j] = '\0';

        for (int j = 0; s[i].op1[j]; j++)
            if (s[i].op1[j] == ' ') {
                memmove(&s[i].op1[j], &s[i].op1[j + 1],
                        strlen(&s[i].op1[j]));
                j--;
            }

        for (int j = 0; s[i].op2[j]; j++)
            if (s[i].op2[j] == ' ') {
                memmove(&s[i].op2[j], &s[i].op2[j + 1],
                        strlen(&s[i].op2[j]));
                j--;
            }
    }

    printf("\nAfter Constant Propagation:\n");

    for (i = 0; i < n; i++) {

        /*
         * Replace operands with previously known constants.
         */
        for (int j = 0; j < i; j++) {

            if (strcmp(s[i].op1, s[j].lhs) == 0 &&
                isConstant(s[j].op1)) {
                strcpy(s[i].op1, s[j].op1);
            }

            if (strcmp(s[i].op2, s[j].lhs) == 0 &&
                isConstant(s[j].op1)) {
                strcpy(s[i].op2, s[j].op1);
            }
        }

        if (s[i].op == '=') {
            printf("%s = %s\n", s[i].lhs, s[i].op1);
        }
        else if (isConstant(s[i].op1) &&
                 isConstant(s[i].op2)) {

            int a = atoi(s[i].op1);
            int b = atoi(s[i].op2);

            switch (s[i].op) {
                case '+': value = a + b; break;
                case '-': value = a - b; break;
                case '*': value = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("%s = %s %c %s\n",
                               s[i].lhs, s[i].op1,
                               s[i].op, s[i].op2);
                        continue;
                    }
                    value = a / b;
                    break;
            }

            printf("%s = %d\n", s[i].lhs, value);

            // Store calculated constant for later propagation
            sprintf(s[i].op1, "%d", value);
        }
        else {
            printf("%s = %s %c %s\n",
                   s[i].lhs,
                   s[i].op1,
                   s[i].op,
                   s[i].op2);
        }
    }

    return 0;
}
