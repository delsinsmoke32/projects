#include <stdio.h>
//c'è una soluzione O(1), poi ci penso
int limit = 100000;
int main(void){
    int iter = 3;
    unsigned long sum = 0;
    while (iter < limit){
        sum += iter;
        iter += 3;
    }
    iter = 5;
    while (iter < limit){
        if (iter % 15 != 0){
            sum += iter;
        }
        iter += 5;
    }
    printf("%lu\n", sum);
}