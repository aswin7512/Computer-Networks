#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

const char symbols[]      = { 'i', '+', '-', '*', '/', '^', '(', ')', '$' };
const char *symbol_names[]= { "id","+","-","*","/","^","(",")","$" };
#define NSYM 9

const char table[NSYM][NSYM] = {
    /* id */ {' ', '>', '>', '>', '>', '>', ' ', '>', '>'},
    /* +  */ {'<', '>', '>', '<', '<', '<', '<', '>', '>'},
    /* -  */ {'<', '>', '>', '<', '<', '<', '<', '>', '>'},
    /* *  */ {'<', '>', '>', '>', '>', '<', '<', '>', '>'},
    /* /  */ {'<', '>', '>', '>', '>', '<', '<', '>', '>'},
    /* ^  */ {'<', '>', '>', '>', '>', '<', '<', '>', '>'},
    /* (  */ {'<', '<', '<', '<', '<', '<', '<', '=', ' '},
    /* )  */ {' ', '>', '>', '>', '>', '>', ' ', '>', '>'},
    /* $  */ {'<', '<', '<', '<', '<', '<', '<', ' ', ' '}
};

int index_of(char c) {
    for (int i = 0; i < NSYM; i++)
        if (symbols[i] == c) return i;
    return -1;
}

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop(void)     { return stack[top--]; }
char peek(void)     { return stack[top]; }

void print_stack(void) {
    for (int i = 0; i <= top; i++) {
        if (stack[i] == 'i') printf("id");
        else printf("%c", stack[i]);
    }
}

int tokenize(const char *expr, char *tokens) {
    int n = 0, len = strlen(expr);
    for (int i = 0; i < len; i++) {
        char c = expr[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            tokens[n++] = 'i';
            while (i + 1 < len && isalnum((unsigned char)expr[i + 1])) i++;
        } else if (strchr("+-*/^()", c)) {
            tokens[n++] = c;
        } else {
            printf("Unrecognized character '%c' in input.\n", c);
            exit(1);
        }
    }
    tokens[n++] = '$';
    return n;
}

/* ---------------- Parser ---------------- */
int parse(const char *tokens, int ntok) {
    int ip = 0;              // input pointer
    top = -1;
    push('$');

    printf("\n%-20s %-20s %-10s\n", "STACK", "INPUT", "ACTION");
    printf("--------------------------------------------------------\n");

    while (1) {
        char a = peek();
        char b = tokens[ip];

        // print current configuration
        printf("%-20.*s", 0, "");
        {
            char sbuf[MAX] = {0};
            int p = 0;
            for (int i = 0; i <= top; i++) {
                if (stack[i] == 'i') { sbuf[p++]='i'; sbuf[p++]='d'; }
                else sbuf[p++] = stack[i];
            }
            sbuf[p] = '\0';
            char ibuf[MAX] = {0};
            int q = 0;
            for (int i = ip; i < ntok; i++) {
                if (tokens[i] == 'i') { ibuf[q++]='i'; ibuf[q++]='d'; }
                else ibuf[q++] = tokens[i];
            }
            ibuf[q] = '\0';
            printf("%-20s %-20s", sbuf, ibuf);
        }

        if (a == '$' && b == '$') {
            printf("%-10s\n", "Accept");
            return 1;
        }

        int ra = index_of(a);
        int rb = index_of(b);
        if (ra == -1 || rb == -1) {
            printf("%-10s\n", "Error");
            return 0;
        }

        char rel = table[ra][rb];

        if (rel == '<' || rel == '=') {
            printf("%-10s\n", "Shift");
            push(b);
            ip++;
        } else if (rel == '>') {
            //reduce: pop until the exposed stack-top has '<' relation with the symbol most recently popped
            printf("%-10s\n", "Reduce");
            char popped;
            do {
                popped = pop();
                if (top < 0) { printf("Error: stack underflow.\n"); return 0; }
            } while (table[index_of(peek())][index_of(popped)] != '<');
        } else {
            printf("%-10s\n", "Error");
            return 0;
        }
    }
}

int main(void) {
    char expr[MAX];
    char tokens[MAX];

    printf("Operator Precedence Parser\n");
    printf("Grammar operators supported: + - * / ^ ( )   (operands = id)\n");
    printf("Enter an expression (e.g. id+id*(id-id)  or  a+b*(c-d) ):\n> ");

    if (!fgets(expr, sizeof(expr), stdin)) return 0;
    expr[strcspn(expr, "\n")] = '\0';

    int ntok = tokenize(expr, tokens);

    int accepted = parse(tokens, ntok);

    printf("\nResult: %s\n", accepted ? "Expression is VALID (accepted)."
                                       : "Expression is INVALID (rejected).");
    return 0;
}
