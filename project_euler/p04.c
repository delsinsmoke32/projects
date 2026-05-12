#include <stdio.h>
#include <string.h>

int main(void){
    char buf[12];
    int max = 0;
    int len = 0;
    int flag = 0;
    for(int i = 100; i < 1000; i++){
        for (int j = 100; j < 1000; j++){
            flag = 1;
            bzero(buf, 12);
            sprintf(buf, "%d", i * j);
            len = strlen(buf);
            for (int z = 0; z < (int) len/2; z++){
                if (buf[z] != buf[len - 1 - z]){
                    flag = 0;
                    break;
                }
            }
            if (flag){
                if (i * j > max){
                    printf("%d %d\n", i, j);
                    max = i * j;
                }
            }
        }
    }

    printf("%d\n", max);
}