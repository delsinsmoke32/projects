#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define BOID_SIZE 10
#define BOIDS 20
#define MAX_SPEED 5

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
    Vector2 center;
    Vector2 speed_abs;
    Vector2 speed;
    float angle;
    float size;
} Boid;

/*
Calculate the three vertices by placing them 
apart on the circle:
Vertex 1: x + rcos(theta), y + rsin(theta)
Vertex 2: x + rcos(theta + 120), y + rsin(theta + 120)
Vertex 3: x + rcos(theta - 120), y + rsin(theta - 120)
*/

/*
Regole generali dei Boids:
1. Separazione (Separation): I boids sterzano per evitare di sovraffollarsi o scontrarsi con i vicini.
2. Allineamento (Alignment): I boids sterzano per allinearsi alla direzione e velocità media dei vicini.
3. Coesione (Cohesion): I boids si muovono verso il centro di massa (baricentro) dei vicini.
*/



void InitBoids(Boid boids[], u32 size){
    for (u32 i = 0; i < size; i++){
        boids[i].size = BOID_SIZE;
        boids[i].center = (Vector2) {GetRandomValue(boids[i].size, WIDTH - boids[i].size), GetRandomValue(boids[i].size, HEIGHT - boids[i].size)};
        boids[i].angle = GetRandomValue(0, 359);
        boids[i].speed_abs = (Vector2) {GetRandomValue(1, MAX_SPEED), GetRandomValue(1, MAX_SPEED)};
        boids[i].speed = (Vector2) {boids[i].speed_abs.x * cosf(boids[i].angle * PI/180.0), boids[i].speed_abs.y * sinf(boids[i].angle * PI/180.0)};
    }
}

void UpdateBoids(Boid boids[], u32 size){
    for (u32 i = 0; i < size; i++){
        boids[i].center = (Vector2) {boids[i].center.x += boids[i].speed.x, boids[i].center.y += boids[i].speed.y};
        boids[i].angle += -1;
        boids[i].speed = (Vector2) {boids[i].speed_abs.x * cosf(boids[i].angle * PI/180.0), boids[i].speed_abs.y * sinf(boids[i].angle * PI/180.0)};
        if (boids[i].center.x < 0) boids[i].center.x = WIDTH;
        if (boids[i].center.x > WIDTH) boids[i].center.x = 0;
        if (boids[i].center.y < 0) boids[i].center.y = HEIGHT;
        if (boids[i].center.y > HEIGHT) boids[i].center.y = 0;
    } 
}

void DrawBoid(Boid boid){
    //NON CAMBIARE L'ORDINE DEI VETTORI O LA DRAWTRIANGLE NON FUNZIONA
    Vector2 vertex1 = (Vector2) {boid.center.x + boid.size * cosf(boid.angle * PI / 180.0), boid.center.y + boid.size * sinf(boid.angle * PI / 180.0)};
    Vector2 vertex2 = (Vector2) {boid.center.x + boid.size * 0.8 * cosf((boid.angle) * PI / 180.0 + 2.4), boid.center.y + boid.size * 0.8 * sinf((boid.angle) * PI / 180.0 + 2.4)};
    Vector2 vertex3 = (Vector2) {boid.center.x + boid.size * 0.8 * cosf((boid.angle) * PI / 180.0 - 2.4), boid.center.y + boid.size * 0.8 * sinf((boid.angle) * PI / 180.0 - 2.4)};
    DrawTriangleLines(vertex1, vertex2, vertex3, RAYWHITE);
}

void DrawBoids(Boid boids[], u32 size){
    for (u32 i = 0; i < size; i++){
        DrawBoid(boids[i]);
    }
}

int main(void){
    InitWindow(WIDTH, HEIGHT, "Flocking Simulation");
    SetTargetFPS(60);
    Boid boids[BOIDS];
    InitBoids(boids, BOIDS);
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            UpdateBoids(boids, BOIDS);
            DrawBoids(boids, BOIDS);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
