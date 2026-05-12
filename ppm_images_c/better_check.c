#include <stdio.h>

int main(void){

    FILE *f = fopen("img.ppm", "w");
    int w = 16 * 60;
    int h = 9 * 60;
    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", w, h);
    fprintf(f, "255\n");
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            if ((x/60 + y/60) % 2){
                fputc(0xFF, f);
                fputc(0x00, f);
                fputc(0x00, f);
            } else {
                fputc(0x00, f);
                fputc(0x00, f);
                fputc(0xFF, f);
            }
        }
    }
    fclose(f);
    printf("Generata immagine.\n");
    return 0;
}