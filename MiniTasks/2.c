// Matrix Initialization:
// User specifies the dimensions of the matrix.
// Dynamically allocate memory for the matrix and initialize it with user-provided values.
// Threads and Their Tasks:
// Thread 1: Finds and prints the maximum value in the matrix.
// Thread 2: Finds and prints the minimum value in the matrix.
// Thread 3: Prints the diagonals of the matrix (both primary and secondary).
// Thread 4: Computes and prints the average of all elements in the matrix.
// Մատրիցի վրա փոփոխություն անել չի կարելի։
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    int** mat;
    int row;
    int col;
}args;

void * create_thread1 (void* arg) {
    args* tmp = (args*)arg;
    int ** matrix = tmp -> mat;
    int row = tmp -> row;
    int col = tmp -> col;
    int max = INT_MIN;
    for(int i = 0; i < row; ++i) { 
        for(int j = 0; j < col; ++j) {
            if(max < matrix[i][j]){
                max = matrix[i][j];
            }
        }
    }
    printf("First thread Maximum: %d\n", max);
    return NULL;
}
void * create_thread2 (void* arg) {
    args* tmp = (args*)arg;
    int ** matrix = tmp -> mat;
    int row = tmp -> row;
    int col = tmp -> col;
    int min = INT_MAX;
    for(int i = 0; i < row; ++i) { 
        for(int j = 0; j < col; ++j) {
            if(min > matrix[i][j]){
                min = matrix[i][j];
            }
        }
    }
    printf("Second thread Minimum: %d\n", min);
    return NULL;
}
void * create_thread3 (void* arg) {
    args* tmp = (args*)arg;
    int ** matrix = tmp -> mat;
    int row = tmp -> row;
    int col = tmp -> col;
    int max = INT_MIN;
    for(int i = 0; i < row; ++i) { 
        for(int j = 0; j < col; ++j) {
            if (i == j || i == col - 1 - j) {
                printf("%d",matrix[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return NULL;
    
}
void * create_thread4 (void* arg) {
    args* tmp = (args*)arg;
    int ** matrix = tmp -> mat;
    int row = tmp -> row;
    int col = tmp -> col;
    int *sum = malloc(sizeof(int) * 1);
    *sum = 0;
    for(int i = 0; i < row; ++i) { 
        for(int j = 0; j < col; ++j) {
            *sum += matrix[i][j];
        }
    }
    *sum = *sum / (row*col);
    
    return (void*)sum;
}


int main() {
    args arguments;


    printf("Enter  row: ");
    scanf("%d", &arguments.row);
    printf("Enter  col: ");
    scanf("%d", &arguments.col);

    arguments.mat = (int**)malloc(sizeof(int*) * arguments.row);
    
    for (int i = 0; i < arguments.row; i++) {
       arguments.mat[i] = (int*)malloc(sizeof(int) * arguments.col);
    }
    printf("Print matrix: \n");
    for (int i = 0; i < arguments.row; i++) {
        for (int j = 0; j < arguments.col; j++) {
            scanf("%d", &arguments.mat[i][j]);
        }   
    }
    


    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;

    pthread_create(&thread1, NULL, create_thread1, (void*)&arguments);
    pthread_create(&thread2, NULL, create_thread2, (void*)&arguments);
    pthread_create(&thread3, NULL, create_thread3, (void*)&arguments);
    pthread_create(&thread4, NULL, create_thread4, (void*)&arguments);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    void* res;
    pthread_join(thread4, &res);
    printf("4thread: %d\n", *((int*)res));
    
    // int res = 0;
    // pthread_join(thread4, (void*)&res);
    // printf("4thread: %d", res);


    return 0;
}
