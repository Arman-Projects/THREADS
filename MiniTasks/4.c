#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct {
    int *arr;
    int size;
}arguments;
int getFibonacciNumber(int n) {
    if (n <= 1)
        return n;
    else
        return getFibonacciNumber(n-1) + getFibonacciNumber(n-2);
}   
void *create_thread(void * args) {
    arguments *arg = (arguments*)args;
    static int i = 0;
    arg->arr[i] = getFibonacciNumber(i);
    ++i;
    pthread_exit(NULL);
}
int main() {
    arguments* args = (arguments*)malloc(sizeof(arguments));
    printf("Print number: ");
    scanf("%d", &args->size);
    args->arr = (int *)malloc(args->size * sizeof(int));
    pthread_t thread[args->size];
    
    for (int i = 0; i < args->size; ++i) {
        pthread_create(&thread[i], NULL, create_thread, (void*)args);
    }
    for (int i = 0; i < args->size; ++i) {
        pthread_join(thread[i], NULL);
    }
    for (int i = 0; i < args->size; ++i) {
        printf("%d ", args->arr[i]);
    }

    free(args);
    return 0;
}
