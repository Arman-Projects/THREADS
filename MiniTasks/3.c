// Գրել ծրագիր, որը կստեղծի 2 thread, 1-ին thread-ի կանչած 
// ֆունկցիան դինամիկ հիշողությունից կվերցնի զանգված և կլցնի 
// զանգվածի մեջ մինչև N-ը եղած բոլոր պարզ թվերը։ 2-րդ thread-ը 
// ստանալու է 1-ին thread-ում ստեղծված զանգվածը և կտպի էկրանին 
// զանգվածի տարրերը։ Ինչպես նաև կազատի դինամիկ հիշողությունից 
// վերցրած տարածքը։
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 101
typedef struct {
    int *arr;
    int size;
}arguments;

int isPrime(int x) {
    if (x <= 1) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;
    for (int i = 3; i * i <= x; i += 2)
        if (x % i == 0)
            return 0;
    return 1;
}
void * create_thread1(void *args) {
    arguments *arg = (arguments *)args;
    arg->size = 0;
    for (int i = 0; i <= N; ++i) {
        if(isPrime(i)){
            ++arg->size;
        }
    }
    arg->arr = (int *)malloc(arg->size * sizeof(int));
    int j = 0;
    for (int i = 0; i <= N; ++i) {
        if(isPrime(i)){
            arg->arr[j++] = i;
        }
    }
    pthread_exit(NULL);
}
void * create_thread2(void *args) {
arguments *arg = (arguments *)args;
    for (int i = 0; i < arg->size; ++i) {
        printf("%d ", arg->arr[i]);
    }
    free(arg->arr);
    return NULL;
}

int main () {
    arguments *args = (arguments *)malloc(sizeof(arguments));
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1, NULL, create_thread1, (void*)args);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, create_thread2, (void*)args);
    pthread_join(thread2, NULL);
    printf("\nPrime numbers from 0 to %d are: ", N);

    free(args);
    return 0;
}
