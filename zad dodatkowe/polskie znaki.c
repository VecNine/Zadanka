#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        return 1;
    }

    int zrodlo = open(argv[1], O_RDONLY);
    if (zrodlo == -1) {
        perror("Blad otwarcia pliku wejsciowego");
        return 1;
    }

    char nowa_nazwa[256] = "nowy_";
    strcat(nowa_nazwa, argv[1]);

    int cel = open(nowa_nazwa, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cel == -1) {
        close(zrodlo);
        return 1;
    }

    unsigned char b1, b2;
    while (read(zrodlo, &b1, 1) == 1) {
        if (b1 == 0xC3 || b1 == 0xC4 || b1 == 0xC5) {
            if (read(zrodlo, &b2, 1) == 1) {
                if (b1 == 0xC4 && b2 == 0x85)      write(cel, "a", 1);
                else if (b1 == 0xC4 && b2 == 0x84) write(cel, "A", 1);
                else if (b1 == 0xC4 && b2 == 0x87) write(cel, "c", 1);
                else if (b1 == 0xC4 && b2 == 0x86) write(cel, "C", 1);
                else if (b1 == 0xC4 && b2 == 0x99) write(cel, "e", 1);
                else if (b1 == 0xC4 && b2 == 0x98) write(cel, "E", 1);
                else if (b1 == 0xC5 && b2 == 0x82) write(cel, "l", 1);
                else if (b1 == 0xC5 && b2 == 0x81) write(cel, "L", 1);
                else if (b1 == 0xC5 && b2 == 0x84) write(cel, "n", 1);
                else if (b1 == 0xC5 && b2 == 0x83) write(cel, "N", 1);
                else if (b1 == 0xC3 && b2 == 0xB3) write(cel, "o", 1);
                else if (b1 == 0xC3 && b2 == 0x93) write(cel, "O", 1);
                else if (b1 == 0xC5 && b2 == 0x9B) write(cel, "s", 1);
                else if (b1 == 0xC5 && b2 == 0x9A) write(cel, "S", 1);
                else if (b1 == 0xC5 && b2 == 0xBC) write(cel, "z", 1);
                else if (b1 == 0xC5 && b2 == 0xBB) write(cel, "Z", 1);
                else if (b1 == 0xC5 && b2 == 0xBA) write(cel, "z", 1);
                else if (b1 == 0xC5 && b2 == 0xB9) write(cel, "Z", 1);
                else {
                    write(cel, &b1, 1);
                    write(cel, &b2, 1);
                }
            }
        } else {
            write(cel, &b1, 1);
        }
    }

    close(zrodlo);
    close(cel);

    return 0;
}