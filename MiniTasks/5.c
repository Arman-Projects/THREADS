#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//Create piramida with threads
typedef struct {
    int size;
    char sym;
}arguments;
void *print_piramida(void *arg) {
    arguments *args = (arguments*)arg;
    char sym = args -> sym;
    int size = args -> size;
    static int i = 0;
    // int line = 0;
    for ( ; i < size; ) {
        for (int j = 0; j < size - i - 1; j++) {
            printf(" ");
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            printf("%c", sym);
        }
        printf("\n");
        ++i;
        break;
    }

    return NULL;
}
int main() {
    arguments *arg = (arguments *)malloc(sizeof(arguments));

    printf("Print Symbol: ");
    scanf("%c", &(arg -> sym));
    printf("Size:");
    scanf("%d", &(arg -> size));
    pthread_t threads[arg -> size];
    for (int i = 0; i < arg -> size; i++) {
        pthread_create(&threads[i], NULL, print_piramida, (void *)arg);
        sleep(1);
    }
    for (int i = 0; i < arg -> size; i++) {
        pthread_join(threads[i], NULL);
    }
    // pthread_create(&threads[0], NULL, print_piramida, (void*)arg);
    // pthread_join(threads[0], NULL);
    free(arg);
    
    return 0;    
}
