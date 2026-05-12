#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <stdlib.h>

#define WIDTH 600
#define HEIGHT 600
#define SQ_SIZE 12   
#define THRESHOLD 90

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

/*
REGOLE:
Qualsiasi cella viva con meno di due celle vive adiacenti muore, come per effetto d'isolamento;
Qualsiasi cella viva con due o tre celle vive adiacenti sopravvive alla generazione successiva;
Qualsiasi cella viva con più di tre celle vive adiacenti muore, come per effetto di sovrappopolazione;
Qualsiasi cella morta con esattamente tre celle vive adiacenti diventa una cella viva, come per effetto di riproduzione.
*/

/*
IMPLEMENTAZIONE POSSIBILE:
boh basilare, check di ogni quadratino (performance ftw) dei vicini, dove un quadratino corrisponde a una posizione
in una matrice. Più la dimensione dei quadratini si abbassa, più diventa pesante. Forse caching aiuta?
*/

int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};
int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};

bool matrix[WIDTH/SQ_SIZE][HEIGHT/SQ_SIZE] = {false};

void Init(){
    u32 thresh = THRESHOLD;
    for (int i = 0; i < WIDTH/SQ_SIZE; i++){
        for (int j = 0; j < HEIGHT/SQ_SIZE; j++){
            u32 num = arc4random_uniform(100);
            if (num >= thresh){
                matrix[i][j] = true;
            }
        }
    }
    return;
}

u32 CalculateNeighbors(int i, int j){
    u32 count = 0;
    for (int z = 0; z < 8; z++) {
        int ni = i + dr[z];
        int nj = j + dc[z];

        // Boundary check
        if (ni >= 0 && ni < WIDTH/SQ_SIZE && nj >= 0 && nj < HEIGHT/SQ_SIZE) {
            if (matrix[ni][nj]) count++;
        }
    }   
    return count;
}   

void UpdateState(){
    u32 count;
    for (u32 i = 0; i < WIDTH/SQ_SIZE; i++){
        for (u32 j = 0; j < HEIGHT/SQ_SIZE; j++){
            count = CalculateNeighbors(i, j);
            if (!matrix[i][j] && count == 3){
                matrix[i][j] = true;
                continue;
            }
            if (matrix[i][j] && count < 2){
                matrix[i][j] = false;
                continue;
            }
            if (matrix[i][j] && count > 3){
                matrix[i][j] = false;
                continue;
            }
            if (matrix[i][j] && count > 1 && count < 4){
                continue;
            }
        }
    }
    return;
}

void DrawMatrix(){
    for (int i = 0; i < WIDTH/SQ_SIZE; i++){
        for (int j = 0; j < HEIGHT/SQ_SIZE; j++){
            if (matrix[i][j]){
                DrawRectangle(i * SQ_SIZE, j * SQ_SIZE, SQ_SIZE, SQ_SIZE, RAYWHITE);
            } else {
                DrawRectangle(i * SQ_SIZE, j * SQ_SIZE, SQ_SIZE, SQ_SIZE, BLACK);
            }
        }
    }
}




int main(void){
    Init();
    InitWindow(WIDTH, HEIGHT, "Conway's Game of Life");
    SetTargetFPS(10);
    while (!WindowShouldClose()){
        BeginDrawing();
            if (IsKeyPressed(KEY_R)){
                for (int i = 0; i < WIDTH/SQ_SIZE; i++){
                    for (int j = 0; j < HEIGHT/SQ_SIZE; j++){
                        matrix[i][j] = false;
                    }
                }
                Init();
            }
            ClearBackground(BLACK);
            UpdateState();
            DrawMatrix();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
