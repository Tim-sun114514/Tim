#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024

char encryptChar(char ch, int shift) {
    if (ch >= 'A' && ch <= 'Z') {
        return (char)('A' + (ch - 'A' + shift) % 26);
    }

    if (ch >= 'a' && ch <= 'z') {
        return (char)('a' + (ch - 'a' + shift) % 26);
    }

    return ch;
}

void caesarEncrypt(char text[], int shift) {
    int i;

    shift = shift % 26;
    if (shift < 0) {
        shift += 26;
    }

    for (i = 0; text[i] != '\0'; i++) {
        text[i] = encryptChar(text[i], shift);
    }
}

int main(void) {
    char text[MAX_TEXT_LENGTH];
    int shift;

    printf("请输入要加密的文本: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("读取文本失败。\n");
        return 1;
    }

    text[strcspn(text, "\n")] = '\0';

    printf("请输入位移量: ");
    if (scanf("%d", &shift) != 1) {
        printf("位移量输入无效。\n");
        return 1;
    }

    caesarEncrypt(text, shift);

    printf("加密结果: %s\n", text);

    return 0;
}
