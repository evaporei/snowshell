#include <stdbool.h>
#include <stdio.h>

int main(void) {
    char input[4096];
    int res;

    while (true) {
        printf("⛄️ ");

        res = scanf("%4096s", input);
        if (res == EOF) {
            printf("^D\n");
            printf("❄❅❄❅ Goodbye and stay warm! ❄❅❄❅\n");
            return 0;
        }

        printf("%s\n", input);
    }
    return 0;
}
