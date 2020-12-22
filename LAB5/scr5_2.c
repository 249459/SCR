#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define OUTPUT_FILE_SIZE 10
#define MAX_FILENAME_SIZE 128
int main() {

    const char *outputFileName = "scr";
    int fd = open(outputFileName, O_RDWR); // zapis odczyt
    char *fileInMemory = mmap(NULL, OUTPUT_FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                              fd,
                              0); //ladujemy plik do pamieci
    char filename[MAX_FILENAME_SIZE];
    int child_id = fork();
    if (child_id == 0) {
        execl("/usr/bin/display", "display","-update","1",outputFileName,NULL);
    }
    while (1) {
        printf("Type filename(type E to end):\n"); //
        scanf("%s", filename);//Nowyplik
        if('E' == filename[0]){
            close(fd);
            return 0;
        }
        struct stat sb;
        if (stat(filename, &sb) == -1) { // czytamy rozmiar nowego pliku
            fprintf(stderr, "Cant get size of file\n");
        }
        ftruncate(fd, sb.st_size); // zmieniamy rozmiar pliku(po deskryptorze)
        fileInMemory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                            fd,
                            0);
        int in_fd = open(filename, O_RDONLY); // Otwieramy drugi plik do odczytu
        read(in_fd, fileInMemory, sb.st_size);//Czytamy do pamieci 
        close(in_fd);
        msync(fileInMemory,sb.st_size, MS_SYNC);
    }
}