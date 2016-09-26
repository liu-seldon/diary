#ifndef DIARY_UTILS_HEADER
#define DIARY_UTILS_HEADER

#include <stdio.h>

#define print_num(NUM) printf("%d\n", (NUM))
#define print_str(STR) printf("%s\n", STR)

//const int READ_DIARY = 1;
//const int NEW_DIARY = 1;

int encrypt(char* d, char* s, char* password, int len);
int decrypt(char* d, char* s, char* password, int len);

#endif //DIARY_UTILS_HEADER
