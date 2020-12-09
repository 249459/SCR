#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// SYGNALIZACJA BŁEDÓW
#define CHUNK_SIZE 64
#define PIPE_ERROR -5
#define WRITE_ERROR -4
#define READ_ERROR -3
/**
 *
 * DOPIERO deskrytptora piszacego PO ZAMKNIECIU WYSWIETLA
 *
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr,"Bad program call\n");
        return -1;
    }
    int fileDescriptors[2]; // 0 - deskryptor czytajacy
                            // 1 - deskrytptor piszacy
    if (pipe(fileDescriptors) == -1) {
        return PIPE_ERROR;
    }
    int child_id = fork();
    if (child_id == 0) {
        close(fileDescriptors[1]);
        close(STDOUT_FILENO);//Zamykam wyjscia
        close(STDERR_FILENO);//
        dup2(fileDescriptors[0], STDIN_FILENO);//kopiuje deskryptor pliku do wyjscia 
        execl("/usr/bin/display", "display", NULL);//otwier wskazany program po ścieżce i nazwie
        close(fileDescriptors[0]);// zamykamy czytanie
    } else {
        close(fileDescriptors[0]);
        int file_fd = open(argv[1], O_RDONLY);//otwieramy plik do odczytu
        char buf[CHUNK_SIZE];
        int bytes_read = 0;
        while ((bytes_read = read(file_fd, buf, sizeof(buf))) > 0) {// czytamy z pliku
            if (write(fileDescriptors[1], buf, bytes_read) == -1) {//piszemy do pipe
                return WRITE_ERROR;
            }
        }
        if (bytes_read == -1) {
            printf("Read error\n");
            return READ_ERROR;
        }
        char end = ' ';
        while (end != 'E') {// Czekam zeby zobaczyc czy wyswietli sie przed zamknieciem
            printf("Type 'E' to close write descriptor\n");
            scanf("%c", &end);
        }
        close(fileDescriptors[1]);// Dopiero po tym wyświetla się obrazek
    }
    return 0;
}