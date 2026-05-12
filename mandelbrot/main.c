#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 800

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


void DrawMandelbrotSet(){
    float x = 0;
    float y = 0;
    u32 iteration = 0;
    u32 max_iter = 1000;
    float x_temp = 0;
    float x0_scaled = 0;
    float y0_scaled = 0;
    float scalex = 2.47 / WIDTH; //definito fra -2 e 0.47
    float scaley = 2.24 / HEIGHT; //definito fra -1.12 e 1.12
    float scalecol = 360/100; //fattore di scala per il colore, 100 sembra il migliore
    float hue = 0;
    for (u32 x0 = 0; x0 < WIDTH; x0++){
        for (u32 y0 = 0; y0 < HEIGHT; y0++){
            x0_scaled = -2.0 + (float)(x0 * scalex);
            y0_scaled = -1.12 + (float)(y0 * scaley); 
            iteration = 0;
            x = 0;
            y = 0;
            x_temp = 0;
            while (((x * x + y * y) <= 4) && (iteration < max_iter)){
                x_temp = x*x - y*y + x0_scaled;
                y = 2*x*y + y0_scaled;
                x = x_temp;
                iteration++;
            }
            if (iteration == max_iter){
                DrawPixel(x0, y0, BLACK);
            }
            else {
                hue = iteration * scalecol;
                DrawPixel(x0, y0, ColorFromHSV(hue, 1.0, 1.0));
            }
        }
    }
}


int main(void){
    InitWindow(WIDTH, HEIGHT, "Mandelbrot Set");
    SetTargetFPS(1);
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);
            DrawMandelbrotSet();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
