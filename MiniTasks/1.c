// Գրել ծրագիր, որի կատարման արդյունքում կստեղծվի thread և 
// thread-ը կկանչի ֆունկցիա, որը որպես արգումենտ ստանալու է 
// զանգված և չափ։ Ֆունկցիան վերադարձնելու է զանգվածի տարրերից 
// երրորդ մեծագույնը։ Ֆունկցիայի վերադարձված արժեքը տպել էկրանին։
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <stdlib.h>
typedef struct{
    int * nums;
    int size;
} args;

void* thirdMax(void * arg) {
    args* tmp = (args*)arg;
    long max1 = LONG_MIN;
    long max2 = LONG_MIN;
    long max3 = LONG_MIN;
    int *nums = tmp -> nums;
    int numsSize = tmp -> size;
    for(int i = 0; i < numsSize; ++i) { 
        if (max1 < nums[i]) {
            max3 = max2;
            max2 = max1;
            max1 = nums[i];
        }
        if (max2 < nums[i] && nums[i] != max1) {
            max3 = max2;
            max2 = nums[i];
        }
        if (max3 < nums[i] && nums[i] != max2 && nums[i] != max1) {
            max3 = nums[i];
        }
    }
    if(max3 == LONG_MIN) {
        return (void*)max1;
    }
    return (void*)max3;
}

int main(){

    args arguments;
    arguments.nums = (int*)malloc(sizeof(int) * 5);
    arguments.size = 5;
    printf("Enter %d elements: ", arguments.size);
    for (int i = 0; i < arguments.size; i++) {
       scanf("%d", &arguments.nums[i]);
    }
    
    pthread_t thred;
    int res;
    pthread_create(&thred, NULL, thirdMax, (void*)&arguments);
    pthread_join(thred,(void*)&res);
    printf("%d", res);
    return 0;
}

