#include "utils.h"

int checkError(FILE* f) {
    if (f == NULL) {
        printf("open file error\n");
        return 1;
    }
    return 0;
}
int encrypt(char* destin, char* source, char* password, int len) {
    FILE* d;
    FILE* s;
    int status;
    d = fopen(destin, "wb");
    if (checkError(d)) {
        return 1;
    }
    s = fopen(source, "r");
    if (checkError(s)) {
        return 1;
    }

    char ch;
    int index = 0;
    ch = fgetc(s);
    while (ch != EOF) {
        ch = ch^(password[index++ % len]);
        fputc(ch, d);
        ch = fgetc(s);
    }
    fclose(d);
    fclose(s);
    return 0;
}
