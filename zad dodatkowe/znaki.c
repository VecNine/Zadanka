#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int plik;
    char znak;

    plik=open("win.txt", O_RDONLY);
    while(read(plik, &znak, 1)==1){
        if (znak==13) printf("CR");
        if (znak==10) printf("\nLF");
        printf("%c", znak);
    }
    close(plik);

    printf("\n");
}