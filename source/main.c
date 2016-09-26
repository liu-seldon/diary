#include <stdio.h>
#include "utils.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define DIR_SIZE 200
char CURRENT_DIR[DIR_SIZE];
char* TEMP_FILE_SUFFIX = ".tmp";
char DIARY_PATH[200];
char TEMP_DIARY_PATH[204];
char PASSWORD[200];

int createDiaryFileName() {
    struct tm* p;
    time_t timep;
    time(&timep);
    p = localtime(&timep);
    char buffer[20];
    sprintf(buffer, "%04d%02d%02d%02d%02d%02d", 1900 + p->tm_year,1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

    /*print_str(CURRENT_DIR);*/
    strcpy(DIARY_PATH, CURRENT_DIR);
    int len = strlen(CURRENT_DIR);
    DIARY_PATH[len] = '/';
    DIARY_PATH[len + 1] = '\0';
    strcat(DIARY_PATH, buffer);
    strcpy(TEMP_DIARY_PATH, DIARY_PATH);
    strcat(TEMP_DIARY_PATH, TEMP_FILE_SUFFIX);
    print_str(DIARY_PATH);
    print_str(TEMP_FILE_SUFFIX);
}

int createNewDiary() {
    pid_t pid = 0;
    createDiaryFileName();
    pid = fork();
    if (pid) {
        printf("parent ");
        print_num(getpid());
        int status;
        waitpid(pid, &status, 0);
        encrypt(DIARY_PATH, TEMP_DIARY_PATH, PASSWORD, strlen(PASSWORD));
        remove(TEMP_DIARY_PATH);
        printf("child return num is ");
        print_num(status);
    } else {
        printf("child ");
        print_num(getpid());
        /*sleep(5);*/
        char* argv[] = {"vim", TEMP_DIARY_PATH, (char*)0};
        execv("/usr/bin/vim", argv);
    }
    return 0;
}

int readDiary(char* path) {
    strcpy(TEMP_DIARY_PATH, path);
    strcat(TEMP_DIARY_PATH, TEMP_FILE_SUFFIX);
    pid_t pid = 0;
    decrypt(TEMP_DIARY_PATH, path, PASSWORD, strlen(PASSWORD));
    pid = fork();
    if (pid) {
        printf("read Diary parent ");
        print_num(getpid());
        int status;
        waitpid(pid, &status, 0);
        remove(TEMP_DIARY_PATH);
        printf("child return num is ");
        print_num(status);
    } else {
        printf("read diary child ");
        print_num(getpid());
        /*sleep(5);*/
        char* argv[] = {"cat", TEMP_DIARY_PATH, (char*)0};
        execv("/bin/cat", argv);
    }
    return 0;

}

int main() {
    getcwd(CURRENT_DIR, DIR_SIZE);

    printf("Welcome to liuzeng's diary!\n");
    printf("please input your password:");
    scanf("%s", PASSWORD);
    printf("What can I do for you?\n");
    printf("1 : read diary\n");
    printf("2 : create new diary\n");

    int chose;
    scanf("%d", &chose);
    switch(chose) {
        case 1:
            printf("you chose read diary");
            strcpy(DIARY_PATH, CURRENT_DIR);
            int len = strlen(DIARY_PATH);
            DIARY_PATH[len] = '/';
            DIARY_PATH[len + 1] = '\0';
            char buffer[15];
            printf("please input file name : ");
            int fileName;
            scanf("%s", buffer);
            strcat(DIARY_PATH, buffer);
            print_str(DIARY_PATH);
            readDiary(DIARY_PATH);
            break;
        case 2:
            printf("you chose create new diary\n");
            createNewDiary();
            break;
        default:
            printf("error chose\n");
            return 1;
    }
    return 0;
}
