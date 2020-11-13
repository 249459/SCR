#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMOFITERATIRON 1000

/**
 * signalHandler1 ztarzymuje program po otrzymaniu sygnału i wyswietla numr sygnalu 
 * signalHandler2 wyświetla tylko numer sygnalu 
 * signalHandler3 czeka zadana ilosc iteracji, potem przechodzi 
 * do obsługi w signalHendler2 wyświetla tylko numer sygnalu 
 * 
 * signalHendler4 nie robi nic
 * 
 * Wykonanie cwiczenia :
 * 
 * po kompilacji uruchomienie programu w tle ./a.out &
 * 
 * przekazywanie sygnalow kill -Numer_sygnału(14,15,10 lub 12)
 * 
 * Wnioski:
 *  -Tylko handler1 kończy program z kodem przekaznego sygnalu 
 *  -Implemntacja z tablicami łatwo umożliwła przebadanie wielu konfiguracji 
 *  -Ćwicznie pokazuje w jaki sposób można obchodzić się z sygnałami z wykorzystaniem języka C 
 * 
 */

void signalHandler1(int signalNum) {
    printf("Program stoped by signal with number %d .\n", signalNum);
    exit(signalNum); //Kończy proces
}

void signalHandler2(int signalNum) {
    printf("Program catched signal %d .\n", signalNum);
}
void signalHandler3(int signalNum) {
    printf("Program waits %i itertion of for loop", NUMOFITERATIRON);
    for (int i = 0; i < NUMOFITERATIRON; ++i) {
    }
    printf("Passing signal to signalHandler2\n");
    signal(signalNum, signalHandler2);
}
void signalHandler4(int signal) {
}

int main() {
    int i = 0;
    const int signals[] = {SIGALRM, SIGTERM, SIGUSR1, SIGUSR2};
    const void (*funcPtrArray[4])(int) = {signalHandler1, signalHandler2, signalHandler3, signalHandler4};
    signal(signals[0], funcPtrArray[1]);
    signal(signals[1], funcPtrArray[0]);
    signal(signals[2], funcPtrArray[3]);
    signal(signals[3], funcPtrArray[2]);
    while (1) {
        i++;
        sleep(1);
    }
}
