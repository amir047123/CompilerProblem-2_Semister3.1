#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum TokenType {
    INTEGER_VARIABLE,
    SHORTINT_NUMBER,
    LONGINT_NUMBER,
    FLOAT_VARIABLE,
    FLOAT_NUMBER,
    DOUBLE_NUMBER,
    CHARACTER_VARIABLE,
    BINARY_VARIABLE,
    BINARY_NUMBER,
    INVALID_INPUT
};

int isAlphaNumeric(char c) {
    return isalnum(c) || c == '_';
}

int isBinary(char c) {
    return c == '0' || c == '1';
}

enum TokenType classifyToken(char* token) {
    int len = strlen(token);
    char firstChar = token[0];

    if (firstChar == 'i' || firstChar == 'I') {
        if (isAlphaNumeric(token[1])) {
            return INTEGER_VARIABLE;
        }
    } else if (firstChar >= '1' && firstChar <= '9') {
        if (len >= 1 && len <= 4) {
            int isShortInt = 1;
            for (int i = 1; i < len; i++) {
                if (!isdigit(token[i])) {
                    isShortInt = 0;
                    break;
                }
            }
            if (isShortInt) {
                return SHORTINT_NUMBER;
            }
        } else if (len >= 5) {
            int isLongInt = 1;
            for (int i = 1; i < len; i++) {
                if (!isdigit(token[i])) {
                    isLongInt = 0;
                    break;
                }
            }
            if (isLongInt) {
                return LONGINT_NUMBER;
            }
        }
    } else if ((firstChar >= 'a' && firstChar <= 'h') || (firstChar >= 'A' && firstChar <= 'H') ||
               (firstChar >= 'o' && firstChar <= 'z') || (firstChar >= 'O' && firstChar <= 'Z')) {
        if (isAlphaNumeric(token[1])) {
            return FLOAT_VARIABLE;
        }
    } else if (firstChar == '0') {
        if (len == 1) {
            return BINARY_VARIABLE;
        } else if (token[1] == '.') {
            int i;
            for (i = 2; i < len; i++) {
                if (!isdigit(token[i])) {
                    break;
                }
            }
            if (i < len) {
                return INVALID_INPUT;
            }
            return FLOAT_NUMBER;
        } else if (isBinary(token[1])) {
            for (int i = 2; i < len; i++) {
                if (!isBinary(token[i])) {
                    return INVALID_INPUT;
                }
            }
            return BINARY_NUMBER;
        }
    } else if (firstChar >= '1' && firstChar <= '9') {
        int dotCount = 0;
        for (int i = 1; i < len; i++) {
            if (isdigit(token[i])) {
                continue;
            } else if (token[i] == '.') {
                dotCount++;
                if (dotCount > 1) {
                    return INVALID_INPUT;
                }
            } else {
                return INVALID_INPUT;
            }
        }
        return (dotCount == 1) ? DOUBLE_NUMBER : FLOAT_NUMBER;
    } else if (strncmp(token, "ch_", 3) == 0) {
        if (isAlphaNumeric(token[3])) {
            return CHARACTER_VARIABLE;
        }
    }

    return INVALID_INPUT;
}

int main() {
    char input[100];
    printf("Enter a token: ");
    scanf("%s", input);

    enum TokenType tokenType = classifyToken(input);

    switch (tokenType) {
        case INTEGER_VARIABLE:
            printf("Token is an Integer Variable.\n");
            break;
        case SHORTINT_NUMBER:
            printf("Token is a ShortInt Number.\n");
            break;
        case LONGINT_NUMBER:
            printf("Token is a LongInt Number.\n");
            break;
        case FLOAT_VARIABLE:
            printf("Token is a Float Variable.\n");
            break;
        case FLOAT_NUMBER:
            printf("Token is a Float Number.\n");
            break;
        case DOUBLE_NUMBER:
            printf("Token is a Double Number.\n");
            break;
        case CHARACTER_VARIABLE:
            printf("Token is a Character Variable.\n");
            break;
        case BINARY_VARIABLE:
            printf("Token is a Binary Variable.\n");
            break;
        case BINARY_NUMBER:
            printf("Token is a Binary Number.\n");
            break;
        case INVALID_INPUT:
            printf("Token is Invalid or Undefined.\n");
            break;
    }

    return 0;
}
