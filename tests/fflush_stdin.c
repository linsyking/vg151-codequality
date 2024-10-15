#include <stdio.h>

int main() {
    printf("not check this");

    // Error
    fflush(stdin);

    // OK
    fflush(stdout);
}
