#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arm/signal.h>
#include <sys/signal.h>

volatile sig_atomic_t works = 1;

void sigterm() {
    works = 0;
}

int main(int argc, char *args[]) {
    signal(SIGTERM, sigterm);

    if (argc < 2) {
        printf("Użycie: %s <liczba_początkowa>\n", args[0]);
        return 1;
    }

    int val = atoi(args[1]);

    while (works) {
        val--;
        sleep(1);
    }

    printf("%d\n", val);
    return 0;
}