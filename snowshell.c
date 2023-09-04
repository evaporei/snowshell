#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile pid_t child_pid = 0;

// this only gets called in the parent process context
void int_handler(int dummy) {
    // parent
    if (child_pid == 0) {
        exit(0);
    // child
    } else {
        kill(child_pid, SIGTERM);
        printf("\n");
    }
}

int main(void) {
    char input[4096];
    char **args = NULL;
    char *buf;
    int res = 0, n_spaces = 0;

    signal(SIGINT, int_handler);

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

        // empty Enter/Return key pressed
        if (args == NULL) {
            continue;
        }

        args = realloc(args, sizeof(char *) * n_spaces + 1);
        args[n_spaces] = 0;

        if (strcmp(args[0], "exit") == 0) {
            return args[1] ? atoi(args[1]) : 0;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (!args[1]) {
                goto end_loop;
            }

            res = chdir(args[1]);

            if (res != 0) {
                if (errno == 2) {
                    printf("cd: The directory '%s' does not exist\n", args[1]);
                } else {
                    printf("cd: Failed to change directory\n");
                }
            }

            goto end_loop;
        }

        child_pid = fork();
        if (child_pid == 0) {
            res = execvp(args[0], args);
            // no such file or directory
            if (res == -1 && errno == 2) {
                printf("🌲⛷  %s: command not found\n", args[0]);
            }
            return 0;
        }
        wait(&res);
end_loop:
        free(args);
        args = NULL;
        n_spaces = 0;
        child_pid = 0;
    }

    return 0;
}
