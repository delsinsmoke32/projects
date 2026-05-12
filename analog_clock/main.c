#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <time.h>
#include <math.h>

#define GMT 2
#define WIDTH 800
#define HEIGHT 800
#define RADIUS 250

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

void DrawEdgeLines(){
    for (int i = 0; i < 60; i++){
        DrawLine(WIDTH/2, HEIGHT/2, WIDTH/2 + RADIUS * cosf(i * 6 * DEG2RAD), HEIGHT/2 + RADIUS * sinf(i * 6 * DEG2RAD), BLACK);
    }
    DrawPoly((Vector2) {WIDTH/2, HEIGHT/2}, 50, RADIUS - 25, 0, RAYWHITE);
    for (int i = 0; i < 12; i++){
        DrawLineEx((Vector2) {WIDTH/2, HEIGHT/2}, (Vector2) {WIDTH/2 + RADIUS * cosf(i * 360/12 * DEG2RAD), HEIGHT/2 + RADIUS * sinf(i * 360/12 * DEG2RAD)}, 1.2, BLACK);
    }
    DrawPoly((Vector2) {WIDTH/2, HEIGHT/2}, 50, RADIUS - 40, 0, RAYWHITE);
}

void DrawHands(struct tm *rn){
    int hr = (rn->tm_hour + GMT) % 24;
    int min = rn->tm_min;
    int sec = rn->tm_sec;
    float hr_angle = hr * 30; //*30 perchè considero 12 anzichè 24
    float min_angle = min * 6;
    float sec_angle = sec * 6;
    DrawLineEx((Vector2){WIDTH/2, HEIGHT/2}, (Vector2){WIDTH/2 + (RADIUS - 100) * cosf(hr_angle * DEG2RAD - PI/2), HEIGHT/2 + (RADIUS - 100) * sinf(hr_angle * DEG2RAD - PI/2)}, 2, RED);
    DrawLineEx((Vector2){WIDTH/2, HEIGHT/2}, (Vector2){WIDTH/2 + (RADIUS - 80) * cosf(min_angle * DEG2RAD - PI/2), HEIGHT/2 + (RADIUS - 80) * sinf(min_angle * DEG2RAD - PI/2)}, 2, GREEN);
    DrawLineEx((Vector2){WIDTH/2, HEIGHT/2}, (Vector2){WIDTH/2 + (RADIUS - 60) * cosf(sec_angle * DEG2RAD - PI/2), HEIGHT/2 + (RADIUS - 60) * sinf(sec_angle * DEG2RAD - PI/2)}, 2, BLUE);
}


int main(void){

    /*
    int hr = (rn->tm_hour + GMT) % 24;
    int min = rn->tm_min;
    int sec = rn->tm_sec;

    printf("Ora corrente: %02d:%02d:%02d\n", (rn->tm_hour + GMT) % 24, rn->tm_min, rn->tm_sec);
    */
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "Analog Clock");
    SetTargetFPS(30);
    while (!WindowShouldClose()){
        time_t current_time;
        time(&current_time);
        struct tm *rn = gmtime(&current_time);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawPoly((Vector2) {WIDTH/2, HEIGHT/2}, 50, RADIUS, 0, RAYWHITE);
            DrawEdgeLines();
            DrawHands(rn);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
