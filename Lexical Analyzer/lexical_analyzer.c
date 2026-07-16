#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char str[]) {
    char keywords[][10] = {
        "int", "float", "if", "else", "while",
        "for", "return", "char", "void"
    };

    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char filePath[200];
    FILE *fp;
    char ch;

    printf("Enter the file path: ");
    scanf("%199s", filePath);

    fp = fopen(filePath, "r");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        // Skip whitespace
        if (isspace(ch))
            continue;

        // Identifier or Keyword
        if (isalpha(ch) || ch == '_') {
            char token[100];
            int i = 0;

            do {
                token[i++] = ch;
                ch = fgetc(fp);
            } while (isalnum(ch) || ch == '_');

            token[i] = '\0';

            if (isKeyword(token))
                printf("%s : Keyword\n", token);
            else
                printf("%s : Identifier\n", token);

            if (ch != EOF)
                ungetc(ch, fp);
        }

        // Number
        else if (isdigit(ch)) {
            char token[100];
            int i = 0;

            do {
                token[i++] = ch;
                ch = fgetc(fp);
            } while (isdigit(ch));

            token[i] = '\0';

            printf("%s : Number\n", token);

            if (ch != EOF)
                ungetc(ch, fp);
        }
	// Comments
	else if (ch == '/') {
	    char next = fgetc(fp);

	    // Multi-line comment /* */
	    if (next == '*') {
		while ((ch = fgetc(fp)) != EOF) {
		    if (ch == '*') {
		        ch = fgetc(fp);
		        if (ch == '/')
		            break;
		    }
		}
	    }

	    // Single-line comment //
	    else if (next == '/') {
		while ((ch = fgetc(fp)) != '\n' && ch != EOF);
	    }

	    else {
		printf("/ : Operator\n");
		ungetc(next, fp);
	    }
	}

        // Operators
        else if (strchr("+-*/=%<>", ch)) {
            printf("%c : Operator\n", ch);
        }

        // Special Symbols
        else if (strchr("(){}[];,", ch)) {
            printf("%c : Special Symbol\n", ch);
        }

        // Unknown Characters
        else {
            printf("%c : Unknown\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
