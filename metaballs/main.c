#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 900
#define HEIGHT 600
#define THRESHOLD 1
#define METABALLS 10


typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


typedef struct {
    Color color;
    float x;
    float y;
    float r; //raggio
} Metaball;

Metaball metaballs[METABALLS];

float CalculateDistance2D(float px, float py, i32 i){
    //Raggio al quadrato fratto distanza al quadrato
    return (metaballs[i].r * metaballs[i].r) / ((px - metaballs[i].x) * (px - metaballs[i].x) + (py - metaballs[i].y) * (py - metaballs[i].y));
}

void DrawBall(Metaball ball){
    DrawCircle(ball.x, ball.y, ball.r, ball.color);
    return;
}

void DrawBalls(){
    for (i32 i = 0; i < METABALLS; i++){
        if (metaballs[i].r != 0.0) DrawBall(metaballs[i]);
    }
}

void CalculateInfluence(){
    float influence;
    for (float px = 0; px < WIDTH; px++){
        for (float py = 0; py < HEIGHT; py++){
            influence = 0;
            for (i32 i = 0; i < METABALLS; i++){
                if (metaballs[i].r != 0.0) influence += CalculateDistance2D(px, py, i);
                if (influence > THRESHOLD) DrawPixel(px, py, metaballs[i].color);
            }
        }
    }
}


int main(void){
    bzero(metaballs, METABALLS * sizeof(Metaball));
    i32 count = 0;
    InitWindow(WIDTH, HEIGHT, "Metaballs");
    SetTargetFPS(30);
    while (!WindowShouldClose()){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (count < METABALLS){
                float px = GetMousePosition().x;
                float py = GetMousePosition().y;
                metaballs[count] = (Metaball) {RED, px, py, 50};
                ++count;
            }
        }
        BeginDrawing();
            ClearBackground(BLACK);
            DrawBalls();
            CalculateInfluence();
            if (count > 0){
                metaballs[count-1].x = GetMousePosition().x;
                metaballs[count-1].y = GetMousePosition().y;
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
