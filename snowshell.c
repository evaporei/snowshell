#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char input[4096];
    int res = 0;
    pid_t child_pid, wpid;

    while (true) {
        printf("⛄️ ");

        res = scanf("%4096s", input);
        if (res == EOF) {
            printf("^D\n");
            printf("❄❅❄❅ Goodbye and stay warm! ❄❅❄❅\n");
            return 0;
        }

        if ((child_pid = fork()) == 0) {
            execvp(input, NULL);
            return 0;
        }
        wpid = wait(&res);
    }
    return 0;
}
