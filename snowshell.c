#include <stdbool.h>
#include <stdio.h>

int main(void) {
    char input[4096];
    while (true) {
        printf("⛄️ ");
        scanf("%4096s", input);
        printf("%s\n", input);
    }
    return 0;
}
