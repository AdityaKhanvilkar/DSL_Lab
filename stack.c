#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

// -------- String Stack --------
char stack[SIZE][SIZE];
int top = -1;

void push(char str[]) {
    if (top < SIZE - 1) {
        strcpy(stack[++top], str);
    }
}

void pop(char str[]) {
    if (top >= 0) {
        strcpy(str, stack[top--]);
    }
}

int isOperand(char ch) {
    return isalnum((unsigned char)ch); // letter or digit
}

// -------- Operator Precedence --------
int icp(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 4;
    if (ch == '(') return 5;
    return 0;
}

int isp(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;
    if (ch == '(') return 0;
    return 0;
}

void reverseStr(char str[]) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// -------- Infix → Postfix --------
void infixToPostfix(char inexp[]) {
    char postexp[SIZE], opstack[SIZE];
    int optop = -1, i = 0, k = 0;
    char tkn;

    while ((tkn = inexp[i]) != '\0') {
        if (isOperand(tkn)) {
            postexp[k++] = tkn;
        } else if (tkn == '(') {
            opstack[++optop] = tkn;
        } else if (tkn == ')') {
            while (optop >= 0 && opstack[optop] != '(') {
                postexp[k++] = opstack[optop--];
            }
            if (optop >= 0) optop--; // remove '('
        } else {
            while (optop >= 0 && isp(opstack[optop]) >= icp(tkn)) {
                postexp[k++] = opstack[optop--];
            }
            opstack[++optop] = tkn;
        }
        i++;
    }
    while (optop >= 0) {
        postexp[k++] = opstack[optop--];
    }
    postexp[k] = '\0';
    printf("Postfix: %s\n", postexp);
}

// -------- Infix → Prefix --------
void infixToPrefix(char inexp[]) {
    char rev[SIZE], prefexp[SIZE], opstack[SIZE];
    int optop = -1, i = 0, k = 0;
    char tkn;

    strcpy(rev, inexp);
    reverseStr(rev);
    for (int x = 0; rev[x] != '\0'; x++) {
        if (rev[x] == '(') rev[x] = ')';
        else if (rev[x] == ')') rev[x] = '(';
    }

    while ((tkn = rev[i]) != '\0') {
        if (isOperand(tkn)) {
            prefexp[k++] = tkn;
        } else if (tkn == '(') {
            opstack[++optop] = tkn;
        } else if (tkn == ')') {
            while (optop >= 0 && opstack[optop] != '(') {
                prefexp[k++] = opstack[optop--];
            }
            if (optop >= 0) optop--;
        } else {
            while (optop >= 0 && isp(opstack[optop]) > icp(tkn)) {
                prefexp[k++] = opstack[optop--];
            }
            opstack[++optop] = tkn;
        }
        i++;
    }
    while (optop >= 0) {
        prefexp[k++] = opstack[optop--];
    }
    prefexp[k] = '\0';
    reverseStr(prefexp);
    printf("Prefix: %s\n", prefexp);
}

// -------- Prefix → Postfix --------
void prefixToPostfix(char pre[]) {
    char temp[SIZE];
    int len = strlen(pre);
    top = -1;

    for (int i = len - 1; i >= 0; i--) {
        if (isOperand(pre[i])) {
            temp[0] = pre[i]; temp[1] = '\0';
            push(temp);
        } else {
            char op1[SIZE], op2[SIZE], expr[SIZE];
            pop(op1);
            pop(op2);
            sprintf(expr, "%s%s%c", op1, op2, pre[i]);
            push(expr);
        }
    }
    printf("Postfix: %s\n", stack[top]);
}

// -------- Prefix → Infix --------
void prefixToInfix(char pre[]) {
    char temp[SIZE];
    int len = strlen(pre);
    top = -1;

    for (int i = len - 1; i >= 0; i--) {
        if (isOperand(pre[i])) {
            temp[0] = pre[i]; temp[1] = '\0';
            push(temp);
        } else {
            char op1[SIZE], op2[SIZE], expr[SIZE];
            pop(op1);
            pop(op2);
            sprintf(expr, "(%s%c%s)", op1, pre[i], op2);
            push(expr);
        }
    }
    printf("Infix: %s\n", stack[top]);
}

// -------- Postfix → Infix --------
void postfixToInfix(char post[]) {
    char temp[SIZE];
    int len = strlen(post);
    top = -1;

    for (int i = 0; i < len; i++) {
        if (isOperand(post[i])) {
            temp[0] = post[i]; temp[1] = '\0';
            push(temp);
        } else {
            char op2[SIZE], op1[SIZE], expr[SIZE];
            pop(op2);
            pop(op1);
            sprintf(expr, "(%s%c%s)", op1, post[i], op2);
            push(expr);
        }
    }
    printf("Infix: %s\n", stack[top]);
}

// -------- Postfix → Prefix --------
void postfixToPrefix(char post[]) {
    char temp[SIZE];
    int len = strlen(post);
    top = -1;

    for (int i = 0; i < len; i++) {
        if (isOperand(post[i])) {
            temp[0] = post[i]; temp[1] = '\0';
            push(temp);
        } else {
            char op2[SIZE], op1[SIZE], expr[SIZE];
            pop(op2);
            pop(op1);
            sprintf(expr, "%c%s%s", post[i], op1, op2);
            push(expr);
        }
    }
    printf("Prefix: %s\n", stack[top]);
}

// -------- Main --------
int main() {
    char expression[SIZE];
    int choice;

    while (1) {
        printf("\n--- Conversion Menu ---\n");
        printf("1. Infix to Postfix\n");
        printf("2. Infix to Prefix\n");
        printf("3. Prefix to Postfix\n");
        printf("4. Prefix to Infix\n");
        printf("5. Postfix to Infix\n");
        printf("6. Postfix to Prefix\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) return 0;

        switch (choice) {
            case 1:
                printf("Enter Infix expression: ");
                scanf(" %99s", expression);
                infixToPostfix(expression);
                break;
            case 2:
                printf("Enter Infix expression: ");
                scanf(" %99s", expression);
                infixToPrefix(expression);
                break;
            case 3:
                printf("Enter Prefix expression: ");
                scanf(" %99s", expression);
                prefixToPostfix(expression);
                break;
            case 4:
                printf("Enter Prefix expression: ");
                scanf(" %99s", expression);
                prefixToInfix(expression);
                break;
            case 5:
                printf("Enter Postfix expression: ");
                scanf(" %99s", expression);
                postfixToInfix(expression);
                break;
            case 6:
                printf("Enter Postfix expression: ");
                scanf(" %99s", expression);
                postfixToPrefix(expression);
                break;
            case 7:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
