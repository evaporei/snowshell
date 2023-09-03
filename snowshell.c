#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    char input[4096];
    char *args[] = {input, NULL};
    int res = 0;

    while (true) {
        printf("⛄️ ");

        res = scanf("%4096s", input);
        if (res == EOF) {
            printf("^D\n");
            printf("❄❅❄❅ Goodbye and stay warm! ❄❅❄❅\n");
            return 0;
        }

        if (fork() == 0) {
            res = execvp(input, args);
            // no such file or directory
            if (res == -1 && errno == 2) {
                printf("🌲⛷  %s: command not found\n", input);
            }
            return 0;
        }
        wait(&res);
    }

    return 0;
}
