#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Prototipe fungsi
void infixToPostfix(char *infix, char *postfix);
void postfixToInfix(char *postfix, char *infix);
void infixToPrefix(char *infix, char *prefix);
void prefixToInfix(char *prefix, char *infix);
void prefixToPostfix(char *prefix, char *postfix);
void postfixToPrefix(char *postfix, char *prefix);

// Struktur stack
typedef struct {
    char data[MAX][MAX];
    int top;
} Stack;

// Inisialisasi stack
void initStack(Stack *s) {
    s->top = -1;
}

// Cek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push ke stack
void push(Stack *s, char *str) {
    if (s->top < MAX - 1) {
        strcpy(s->data[++(s->top)], str);
    }
}

// Pop dari stack
void pop(Stack *s, char *str) {
    if (!isEmpty(s)) {
        strcpy(str, s->data[(s->top)--]);
    }
}

// Mendapatkan prioritas operator
int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Membalikkan string
void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Fungsi untuk konversi Infix ke Postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (c == ')') {
            char temp[MAX];
            while (!isEmpty(&s)) {
                pop(&s, temp);
                if (temp[0] == '(') break;
                postfix[j++] = temp[0];
            }
        } else {
            while (!isEmpty(&s) && precedence(s.data[s.top][0]) >= precedence(c)) {
                postfix[j++] = s.data[s.top][0];
                s.top--;
            }
            char temp[2] = {c, '\0'};
            push(&s, temp);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = s.data[s.top][0];
        s.top--;
    }
    postfix[j] = '\0';
}

// Fungsi untuk konversi Postfix ke Infix
void postfixToInfix(char *postfix, char *infix) {
    Stack s;
    initStack(&s);
    char op1[MAX], op2[MAX], temp[MAX];

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            push(&s, operand);
        } else {
            pop(&s, op2);
            pop(&s, op1);
            snprintf(temp, MAX, "(%s%c%s)", op1, postfix[i], op2);
            push(&s, temp);
        }
    }
    pop(&s, infix);
}

// Fungsi untuk konversi Infix ke Prefix
void infixToPrefix(char *infix, char *prefix) {
    reverseString(infix);
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }
    infixToPostfix(infix, prefix);
    reverseString(prefix);
}

// Fungsi untuk konversi Prefix ke Infix
void prefixToInfix(char *prefix, char *infix) {
    Stack s;
    initStack(&s);
    char op1[MAX], op2[MAX], temp[MAX];
    reverseString(prefix);

    for (int i = 0; prefix[i] != '\0'; i++) {
        if (isalnum(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            push(&s, operand);
        } else {
            pop(&s, op1);
            pop(&s, op2);
            snprintf(temp, MAX, "(%s%c%s)", op1, prefix[i], op2);
            push(&s, temp);
        }
    }
    pop(&s, infix);
}

// Fungsi untuk konversi Prefix ke Postfix
void prefixToPostfix(char *prefix, char *postfix) {
    Stack s;
    initStack(&s);
    char op1[MAX], op2[MAX], temp[MAX];
    reverseString(prefix);

    for (int i = 0; prefix[i] != '\0'; i++) {
        if (isalnum(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            push(&s, operand);
        } else {
            pop(&s, op1);
            pop(&s, op2);
            snprintf(temp, MAX, "%s%s%c", op1, op2, prefix[i]);
            push(&s, temp);
        }
    }
    pop(&s, postfix);
}

// Fungsi untuk konversi Postfix ke Prefix
void postfixToPrefix(char *postfix, char *prefix) {
    Stack s;
    initStack(&s);
    char op1[MAX], op2[MAX], temp[MAX];

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            push(&s, operand);
        } else {
            pop(&s, op2);
            pop(&s, op1);
            snprintf(temp, MAX, "%c%s%s", postfix[i], op1, op2);
            push(&s, temp);
        }
    }
    pop(&s, prefix);
}

// Fungsi utama dengan menu interaktif
int main() {
    int choice;
    char infix[MAX], postfix[MAX], prefix[MAX];

    while (1) {
        printf("\nKonversi Ekspresi Aritmatika\n");
        printf("1. Infix ke Postfix\n");
        printf("2. Postfix ke Infix\n");
        printf("3. Infix ke Prefix\n");
        printf("4. Prefix ke Infix\n");
        printf("5. Prefix ke Postfix\n");
        printf("6. Postfix ke Prefix\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);
        getchar();  // Membersihkan buffer input

        switch (choice) {
            case 1:
                printf("Masukkan ekspresi Infix: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0';
                infixToPostfix(infix, postfix);
                printf("Ekspresi Postfix: %s\n", postfix);
                break;
            case 2:
                printf("Masukkan ekspresi Postfix: ");
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = '\0';
                postfixToInfix(postfix, infix);
                printf("Ekspresi Infix: %s\n", infix);
                break;
            case 3:
                printf("Masukkan ekspresi Infix: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0';
                infixToPrefix(infix, prefix);
                printf("Ekspresi Prefix: %s\n", prefix);
                break;
            case 4:
                printf("Masukkan ekspresi Prefix: ");
                fgets(prefix, MAX, stdin);
                prefix[strcspn(prefix, "\n")] = '\0';
                prefixToInfix(prefix, infix);
                printf("Ekspresi Infix: %s\n", infix);
                break;
            case 5:
                printf("Masukkan ekspresi Prefix: ");
                fgets(prefix, MAX, stdin);
                prefix[strcspn(prefix, "\n")] = '\0';
                prefixToPostfix(prefix, postfix);
                printf("Ekspresi Postfix: %s\n", postfix);
                break;
            case 6:
                printf("Masukkan ekspresi Postfix: ");
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = '\0';
                postfixToPrefix(postfix, prefix);
                printf("Ekspresi Prefix: %s\n", prefix);
                break;
            case 7:
                exit(0);
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
    return 0;
}
