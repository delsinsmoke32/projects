#include <stdio.h>

int is_even(int num){
    return (num % 2) == 0;
}

int main(void){
    int num = 0;
    scanf("%d", &num);
    if (is_even(num)){
        printf("E' pari!!!\n");
    } else {
        printf("E' dispari!!!\n");
    }
    printf("Ciao Simo!\n");
    return 0;
}