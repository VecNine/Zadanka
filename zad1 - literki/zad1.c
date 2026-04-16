#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>


volatile sig_atomic_t works = 1;

void handle_sigint() {
    works = 0;
}

void change_letter() {
    char letter = 'A';

    while (works) {
        letter += 1;
        if (letter > 'Z') {
            letter = 'A';
        }
        sleep(1);
    }

    printf("%c\n", letter);
}

int main() {
    signal(SIGTERM, handle_sigint);

    change_letter();

    return 0;
}