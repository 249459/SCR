#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
// KODY BŁEDÓW
#define CHUNK_SIZE 64
#define PIPE_ERROR -5
#define WRITE_ERROR -4
#define READ_ERROR -3
// MYFIFIO wyswietlano z wykorzystaniem programu cat
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        return -1;
    }
    const char *fifo = "MYFIFO";
    if (mkfifo(fifo, 0666) == -1) { //0666 nadaje uprawnienia dla MYFIFO
                                    //Wszyscy moga czytac/pisac z pliku, 0 przed bo w formie binarnej 
        if (errno != EEXIST) {      //sprawdza czy isniteje plik
            fprintf(stderr, "Can not creat fifo file\n");
            return -1;
        }
    }
    int *inputFileDescriptors = malloc((argc - 1) * sizeof(*inputFileDescriptors));//pamiec na deskryptory plików
    int fifoDescriptor = open(fifo, O_WRONLY);//otwieramy FIFO do zapisu
    char buf[CHUNK_SIZE];
    int bytes_read = 0;
    for (int i = 1; i < argc; i++) {
        inputFileDescriptors[i - 1] = open(argv[i], O_RDONLY);//Otwieramy pliki do odczytu
    }
    for (int i = 0; i < argc - 1; i++) {
        while ((bytes_read = read(inputFileDescriptors[i], buf, sizeof(buf))) > 0) {// czytamy z plikow
            if (write(fifoDescriptor, buf, bytes_read) == -1) {// wpsiujemy do fifo
                return WRITE_ERROR;
            }
        }
        if (bytes_read == -1) {
            printf("Read error\n");
            return READ_ERROR;
        }
        close(inputFileDescriptors[i]);// zamykamy pliki
        sleep(3);//czekamy
    }
    close(fifoDescriptor);//zamykamy 
    free(inputFileDescriptors);//zwalniamy pamiec
}
