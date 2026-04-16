#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include "litery.h"

char change_char(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

void change_file() {
    int zrodlo = open("text.txt", O_RDONLY);

    if (zrodlo < 0) {
        return;
    }

    int cel = open("text_cel.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (cel < 0) {
        close(zrodlo);
        return;
    }

    char znak;
    while (read(zrodlo, &znak, 1) == 1) {
        char wr = change_char(znak);
        write(cel, &wr, 1);
    }

    rename("text_cel.txt", "text.txt");

    close(zrodlo);
    close(cel);
}
