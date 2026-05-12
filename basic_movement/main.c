#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define WIDTH 900
#define HEIGHT 600
#define PLAYER_DIMENSION 20

typedef struct {
    u32 x, y, dim, vx, vy;
} Player;

void InitPlayer(Player *player){
    player->dim = PLAYER_DIMENSION;
    player->x = WIDTH/2 - player->dim/2;
    player->y = HEIGHT/2 - player->dim/2;
    player->vx = 0;
    player->vy = 0;
}

void MovePlayer(Player *player){
    player->vx = 0;
    player->vy = 0;
    if (IsKeyDown(KEY_RIGHT)){
        player->vx = 10;
    }
    if (IsKeyDown(KEY_LEFT)){
        player->vx = -10;
    }
    if (IsKeyDown(KEY_UP)){
        player->vy = -10;
    }
    if (IsKeyDown(KEY_DOWN)){
        player->vy = 10;
    }
    if (player->x < player->dim/2) player->x = player->dim/2;
    if (player->x > WIDTH - player->dim) player->x = WIDTH - 2 * player->dim;
    if (player->y < player->dim/2) player->y = player->dim/2;
    if (player->y > HEIGHT - player->dim) player->y = HEIGHT - 2 * player->dim;
    
    player->x += player->vx;
    player->y += player->vy;
}

void DrawPlayer(Player *player){
    DrawRectangle(player->x, player->y, player->dim, player->dim, RED);
}


int main(void){
    InitWindow(WIDTH, HEIGHT, "Basic Movement");
    SetTargetFPS(60);
    Player *player = malloc(sizeof(player));
    if (player == NULL) return 1;
    InitPlayer(player);
    printf("%d", player->dim);
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            MovePlayer(player);
            DrawPlayer(player);
        EndDrawing();
    }
    free(player);
    CloseWindow();
    return 0;
}
