#include <stdio.h>
#include "utils.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DIR_SIZE 200
char CURRENT_DIR[DIR_SIZE];

int main() {
    
    getcwd(CURRENT_DIR, DIR_SIZE);
    print_str(CURRENT_DIR);
    printf("Welcome to liuzeng's diary!\n");
    printf("What can I do for you?\n");
    printf("0 : read diary\n");
    printf("1 : create new diary\n");
    int chose;
    scanf("%d", &chose);
    switch(chose) {
        case 0:
            printf("you chose read diary");
            break;
        case 1:
            printf("you chose create new diary\n");
            break;
        default:
            printf("error chose\n");
            return 1;
    }
    pid_t pid = 0;
    pid = fork();
    if (pid) {
        printf("parent ");
        print_num(getpid());
        int status;
        waitpid(pid, &status, 0); 
        printf("child return num is ");
        print_num(status);
    } else {
        printf("child ");
        print_num(getpid());
        sleep(5);
    }
    return 0;
}
