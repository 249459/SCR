#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS_NUMBER 16
#define SAMPLES_NUMBER 10000
#define SIDE_LENGTH 1
#define H_SIDE_LENGTH 0.5 // SIDE_LENGTH 1/2 = 0.5
#define RADIUS 0.5        // bok to 2r = 1 -> r = 0.5

void *func(void *arg) {
    double square_points = 0;
    double circle_points = 0;
    for (int i = 0; i < SAMPLES_NUMBER; ++i) {
        double x = drand48();
        double y = drand48();
        double x_2 = (x - H_SIDE_LENGTH) * (x - H_SIDE_LENGTH);
        double y_2 = (y - H_SIDE_LENGTH) * (y - H_SIDE_LENGTH);
        if ((x_2 + y_2) <= (RADIUS * RADIUS)) {
            circle_points++;
        }
        square_points++;
    }
    double *result = (double *)arg;
    *result = 4 * (circle_points / square_points);
}

int main() {
    double results[THREADS_NUMBER];
    pthread_t id[THREADS_NUMBER];
    double sum = 0;
    double mean = 0;
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        if (pthread_create(&id[i], NULL, func, (void *)&results[i])) {
            fprintf(stderr, "ERROR");
        }
    }
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        pthread_join(id[i], NULL);
        printf("Thread : %d, returned PI value : %f\n",i,results[i]);
        sum += results[i];
    }
    mean = sum / THREADS_NUMBER;
    printf("Mean value of PI is : %f \n", mean);
}
