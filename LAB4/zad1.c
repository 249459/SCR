#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// SYGNALIZACJA BŁEDÓW
#define CHUNK_SIZE 64
#define PIPE_ERROR -5
#define WRITE_ERROR -4
#define READ_ERROR -3

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
    if (child_id == 0) {//proces pochodny
        close(fileDescriptors[1]);//zamykamy koniec piszacy
        char data_buffer[CHUNK_SIZE];
        int bytes_read = 0;
        while ((bytes_read = read(fileDescriptors[0], data_buffer, sizeof(data_buffer))) > 0) {// czytamy z pipe'a
            fprintf(stdout, "#%.*s#", (int)sizeof(data_buffer), data_buffer);// kopiujemy na stdout
        }
        if (bytes_read == -1) {
            fprintf(stderr,"Read error\n");
            return READ_ERROR;
        }
        close(fileDescriptors[0]);// zamykamy koniec czytajacy
    } else {
        close(fileDescriptors[0]);// zamykamy koniec czytajacy
        int file_fd = open(argv[1], O_RDONLY);//otwieramy plik do odczytu
        char data_buffer[CHUNK_SIZE];
        int bytes_read = 0;
        while ((bytes_read = read(file_fd, data_buffer, sizeof(data_buffer))) > 0) {//czytamy z pliku
            if (write(fileDescriptors[1], data_buffer, bytes_read) == -1) {// piszemy do pipe'a
                return WRITE_ERROR;
            }
        }
        if (bytes_read == -1) {
            fprintf(stderr,"Read error\n");
            return READ_ERROR;
        }
        close(fileDescriptors[1]);
    }
    return 0;
}