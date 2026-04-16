#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

void change_files(char name[]) {
    int zrodlo = open(name, O_RDONLY);
    if (zrodlo < 0) return;

    char nowa_nazwa[256] = "nowy_";
    strncat(nowa_nazwa, name, 250);

    int cel = open(nowa_nazwa, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cel < 0) {
        close(zrodlo);
        return;
    }

    char znak;
    while (read(zrodlo, &znak, 1) == 1) {
        if (znak == '0')      write(cel, "zero", 4);
        else if (znak == '1') write(cel, "jeden", 5);
        else if (znak == '2') write(cel, "dwa", 3);
        else if (znak == '3') write(cel, "trzy", 4);
        else if (znak == '4') write(cel, "cztery", 6);
        else if (znak == '5') write(cel, "pięć", 6);
        else if (znak == '6') write(cel, "sześć", 7);
        else if (znak == '7') write(cel, "siedem", 6);
        else if (znak == '8') write(cel, "osiem", 5);
        else if (znak == '9') write(cel, "dziewięć", 10);
        else write(cel, &znak, 1);
    }

    close(zrodlo);
    close(cel);
}

int main() {
    DIR* sciezka = opendir("/Users/vecnine/Desktop/programowanie/c projects/Zadanka/zad3 - odpowiednik cyfr");
    if (sciezka == NULL) return 1;

    struct dirent* element;

    while ((element = readdir(sciezka)) != NULL) {
        size_t len = strlen(element->d_name);
        if (len < 4 || strcmp(element->d_name + len - 4, ".txt") != 0) {
            continue;
        }

        if (strncmp(element->d_name, "nowy_", 5) == 0) {
            continue;
        }

        pid_t pid = fork();

        if (pid == 0) {
            change_files(element->d_name);
            closedir(sciezka);
            _exit(0);
        } else if (pid < 0) {
            perror("Błąd fork");
        }
    }

    while (wait(NULL) > 0);

    closedir(sciezka);
    return 0;
}