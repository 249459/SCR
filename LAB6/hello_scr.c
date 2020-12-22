#include <pthread.h>
#include <stdio.h>

#define THREADS_NUMBER 16
 
void *thread_func(void* id) {
    long ID = (long)id;
    printf("Hello SCR written by thread %ld\n", ID);

    pthread_exit(NULL);
}

int main() {
    pthread_t id[THREADS_NUMBER];
    for(int i = 0; i < THREADS_NUMBER; ++i) {

        if(pthread_create(&id[i], NULL, thread_func, (void *)id[i])){
            fprintf(stderr, "ERROR");
        }
    }
    pthread_exit(NULL);
    return 0;
}
