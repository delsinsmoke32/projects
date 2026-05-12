#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600
#define STARS 80
#define STAR_SIZE 3
#define Z_CAP 50

typedef struct {
    Vector3 pos;
    float z_old;
} Star;

Star stars[STARS] = {0};
float fov = 3.0;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;



void InitStar(i32 i){
    stars[i].pos = (Vector3) {GetRandomValue(-WIDTH, WIDTH), GetRandomValue(-HEIGHT, HEIGHT), GetRandomValue(1, Z_CAP)};
    stars[i].z_old = stars[i].pos.z;
}


void InitStars(){
    for (i32 i = 0; i < STARS; ++i){
        InitStar(i);
    }
}

void DrawStars(){
    for (i32 i = 0; i < STARS; ++i){
        if (stars[i].pos.z <= 0){
            InitStar(i);
        }
        float xscreen = (stars[i].pos.x / stars[i].pos.z) * fov + WIDTH/2;
        float yscreen = (stars[i].pos.y / stars[i].pos.z) * fov + HEIGHT/2;
        float xscreen_old = (stars[i].pos.x / stars[i].z_old) * fov + WIDTH/2;
        float yscreen_old = (stars[i].pos.y / stars[i].z_old) * fov + HEIGHT/2;
        
        DrawLineEx((Vector2) {xscreen_old, yscreen_old}, (Vector2) {xscreen, yscreen}, STAR_SIZE - 1, RAYWHITE);
        DrawCircleV((Vector2) {xscreen, yscreen}, STAR_SIZE, RAYWHITE);
        stars[i].z_old = stars[i].pos.z;
        stars[i].pos.z--;
    }
}

int main(void){
    InitWindow(WIDTH, HEIGHT, "Starfield Warp");
    InitStars();
    SetTargetFPS(30);
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawStars();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
