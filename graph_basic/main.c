#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define POWER 2.6
#define STEP 0.005

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

Vector2 origin = (Vector2) {WIDTH/2, HEIGHT/2};
int SCALE = 50;

void PlotFunctionXtotheN(float exp){
    for (float x = STEP; x < 100.0; x += STEP){
        float xdec = x - STEP; //x decrementato
        DrawLine(origin.x + xdec * SCALE, origin.y - pow(xdec, exp) * SCALE, origin.x + x * SCALE, origin.y - pow(x, exp) * SCALE, RED);
        DrawLine(origin.x - xdec * SCALE, origin.y - pow(-xdec, exp) * SCALE, origin.x - x * SCALE, origin.y - pow(-x, exp) * SCALE, RED);
    }
    DrawLineEx((Vector2){origin.x, origin.y}, (Vector2){origin.x, 0}, 2, BLACK);
}

void PlotFunctionOneOverX(float num, float den){
    for (float x = STEP * 2; x < 100.0; x += STEP){
        float xdec = x - STEP;
        DrawLine(origin.x + xdec * SCALE, origin.y - num / (xdec * den) * SCALE, origin.x + x * SCALE, origin.y - num / (x * den) * SCALE, RED);
        DrawLine(origin.x - xdec * SCALE, origin.y + num / (xdec * den) * SCALE, origin.x - x * SCALE, origin.y + num / (x * den) * SCALE, RED);
    }
}

void PlotFunctionEtotheX(float exp){
    for (float x = STEP; x < 100.0; x += STEP){
        float xdec = x - STEP;
        DrawLine(origin.x + xdec * SCALE, origin.y - pow(M_E, xdec * exp) * SCALE, origin.x + x * SCALE, origin.y - pow(M_E, x * exp) * SCALE, RED);
        DrawLine(origin.x - xdec * SCALE, origin.y - pow(M_E, -xdec * exp) * SCALE, origin.x - x * SCALE, origin.y - pow(M_E, -x * exp) * SCALE, RED);
    }
}

void PlotFunctionHarmonic(float amplitude, float frequency, float phase){
    for (float x = STEP; x < 100.0; x += STEP){
        float xdec = x - STEP;
        DrawLine(origin.x + xdec * SCALE, origin.y - amplitude * sinf(frequency * xdec + phase) * SCALE, origin.x + x * SCALE, origin.y - amplitude * sinf(frequency * x + phase) * SCALE, RED);
        DrawLine(origin.x - xdec * SCALE, origin.y - amplitude * sinf(frequency * (-xdec) + phase) * SCALE, origin.x - x * SCALE, origin.y - amplitude * sinf(frequency * (-x) + phase) * SCALE, RED);
    }
}

int main(void){
    InitWindow(WIDTH, HEIGHT, "Basic Graphing");
    SetTargetFPS(15);
    while (!WindowShouldClose()){
        float mousewheel = GetMouseWheelMove();
        if (mousewheel != 0){
            SCALE += (int) mousewheel;
            if (SCALE < 1) SCALE = 1;
        }
       
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawLineEx((Vector2){0, HEIGHT/2}, (Vector2){WIDTH, HEIGHT/2}, 2, BLACK);
            DrawLineEx((Vector2){WIDTH/2, 0}, (Vector2){WIDTH/2, HEIGHT}, 2, BLACK);
            PlotFunctionXtotheN(POWER);
            PlotFunctionOneOverX(1,1);
            PlotFunctionEtotheX(1);
            PlotFunctionHarmonic(1, 1, 0);
        EndDrawing();
    }

    return 0;
}
