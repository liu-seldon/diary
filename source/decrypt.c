#include "utils.h"

int decrypt(char* destin, char* s, char* password, int len) {
    encrypt(destin, s, password, len);
}
