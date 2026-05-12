#include <stdio.h>
#define limit 4000000

int main(void){
    int f1 = 0;
    int f2 = 1;
    int f3 = 0;
    int sum = 0;
    while (f3 < limit){
        f3 = f1 + f2;
        if (f3 % 2 == 0){
            sum += f3;
        }
        f1 = f2;
        f2 = f3;
    }
    printf("%d\n", sum);
    return 0;
}   