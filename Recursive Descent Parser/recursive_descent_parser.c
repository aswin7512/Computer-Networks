#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char input[100];
int pos = 0;

void expression();
void term();
void factor();

/* Skip spaces */
void skipSpaces()
{
    while (isspace(input[pos]))
        pos++;
}

void factor()
{
    skipSpaces();

    if (isalpha(input[pos]))
    {
        pos++;

        while (isalnum(input[pos]))
            pos++;
    }

    else if (isdigit(input[pos]))
    {
        while (isdigit(input[pos]))
            pos++;
    }

    else if (input[pos] == '(')
    {
        pos++;

        expression();

        skipSpaces();

        if (input[pos] == ')')
        {
            pos++;
        }
        else
        {
            printf("Invalid expression: missing ')'\n");
            exit(1);
        }
    }

    else
    {
        printf("Invalid expression\n");
        exit(1);
    }

    skipSpaces();
}

void term()
{
    factor();

    skipSpaces();

    while (input[pos] == '*')
    {
        pos++;
        factor();
        skipSpaces();
    }
}

void expression()
{
    term();

    skipSpaces();

    while (input[pos] == '+')
    {
        pos++;
        term();
        skipSpaces();
    }
}

int main()
{
    printf("Enter an expression: ");
    fgets(input, sizeof(input), stdin);

    expression();

    skipSpaces();

    if (input[pos] == '\0')
        printf("Valid expression\n");
    else
        printf("Invalid expression\n");

    return 0;
}
