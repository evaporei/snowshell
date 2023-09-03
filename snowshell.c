#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    char input[4096];
    char **args = NULL;
    char *buf;
    int res = 0, n_spaces = 0;

    while (true) {
        printf("⛄️ ");

        if (fgets(input, 4096, stdin) == NULL) {
            printf("^D\n");
            printf("❄❅❄❅ Goodbye and stay warm! ❄❅❄❅\n");
            return 0;
        }
        input[strcspn(input, "\n")] = 0;

        buf = strtok(input, " ");
        while (buf != NULL) {
            args = realloc(args, sizeof(char *) * ++n_spaces);
            if (args == NULL)
                exit(-1);

            args[n_spaces - 1] = buf;

            buf = strtok(NULL, " ");
        }

        args = realloc(args, sizeof(char *) * n_spaces + 1);
        args[n_spaces] = 0;

        if (strcmp(args[0], "exit") == 0) {
            return args[1] ? atoi(args[1]) : 0;
        }

        if (fork() == 0) {
            res = execvp(args[0], args);
            // no such file or directory
            if (res == -1 && errno == 2) {
                printf("🌲⛷  %s: command not found\n", args[0]);
            }
            return 0;
        }
        wait(&res);
        free(args);
        n_spaces = 0;
    }

    return 0;
}
