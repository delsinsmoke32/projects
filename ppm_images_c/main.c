#include <stdio.h>

int main(void){
    FILE *f = fopen("img.ppm", "w");
    //provo a fare checkerboard
    //i did it yay
    fprintf(f, "P6\n 400 400 255\n");
    for (int i = 0; i < 400 * 400; i++){
        if ((i % 32000) < 16000){
            if ((i % 80) < 40){
                fprintf(f, "%c%c%c", 0, 0, 255);
            } else {
                fprintf(f, "%c%c%c", 255, 0, 0);
            }
        } else {
            if ((i % 80) < 40){
                fprintf(f, "%c%c%c", 255, 0, 0);
            } else {
                fprintf(f, "%c%c%c", 0, 0, 255);
            }
        }
    }
    fclose(f);
    printf("Generata img.ppm\n");
    return 0;
}