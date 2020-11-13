#include <signal.h>
#include <time.h>
#include <unistd.h>
/**
 * Bez wywołania funkcji sleep faktycznie 
 * program był w człówce procesow w funkcji top,
 * wkorzystanie wywołania sleep(1) sprawiło ,że program już w czołówce nie był.
 * 
 * Aby zwiększyć częstoliwość odświeżania fukncji top nalezy skorzystać z wywołania
 * 
 * top -d czas_po_ktorym_odświeżyć
 * 
 * gdzie czas jest podany w sekundach
 * 
 * przykładowe wywołanie 
 * 
 * top -d 0.1
 *  
 */

int main() {
    int i = 0;
    while (1) {
        i++;
        sleep(1);
    }
}