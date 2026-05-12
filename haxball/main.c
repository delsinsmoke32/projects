#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>
#include <stdbool.h>

#define WIDTH 900
#define HEIGHT 600
#define PLAYER_SIZE 16
#define BALL_SIZE 12
#define PLAYER_SPEED_CAP 5
#define BALL_SPEED_CAP 50

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
    Vector2 pos;
    Vector2 abs_speed;
    float angle;
    bool can_kick;
} Player;

typedef struct {
    Vector2 pos;
    Vector2 abs_speed;
    float angle;
} Ball;

/*
*******************
INIZIALIZZAZIONE
*******************
*/

void InitPlayer(Player *player){
    player->pos = (Vector2) {150, HEIGHT/2};
    player->abs_speed = (Vector2) {0, 0};
    player->angle = 0.0;
    player->can_kick = false;
    return;
}

void InitBall(Ball *ball){
    ball->pos = (Vector2) {WIDTH/2, HEIGHT/2};
    ball->abs_speed = (Vector2) {0, 0};
    ball->angle = 0.0;
    return;
}

/*
*******************
AGGIORNAMENTO
*******************
*/

void UpdatePlayer1(Player *player){
    if (IsKeyDown(KEY_A) && player->abs_speed.x > -PLAYER_SPEED_CAP){
        player->abs_speed.x -= 0.3;
    } else {
        if (player->abs_speed.x < 0){
            player->abs_speed.x = ceilf(player->abs_speed.x);
            player->abs_speed.x += 1;
        }
    }

    if (IsKeyDown(KEY_D) && player->abs_speed.x < PLAYER_SPEED_CAP){
        player->abs_speed.x += 0.3;
    } else {
        if (player->abs_speed.x > 0){
            player->abs_speed.x = floorf(player->abs_speed.x);
            player->abs_speed.x -= 1;
        }
    }

    if (IsKeyDown(KEY_S) && player->abs_speed.y < PLAYER_SPEED_CAP){
        player->abs_speed.y += 0.3;
    } else {
        if (player->abs_speed.y > 0){
            player->abs_speed.y = floorf(player->abs_speed.y);
            player->abs_speed.y -= 1;
        }
    }

    if (IsKeyDown(KEY_W) && player->abs_speed.y > -PLAYER_SPEED_CAP){
        player->abs_speed.y -= 0.3;
    } else {
        if (player->abs_speed.y < -0.5){
            player->abs_speed.y = ceilf(player->abs_speed.y);
            player->abs_speed.y += 1;
        }
    }

    if (IsKeyDown(KEY_SPACE)){
        player->can_kick = true;
    } else {
        player->can_kick = false;
    }

    player->pos.x += player->abs_speed.x;
    player->pos.y += player->abs_speed.y;
    if (player->pos.x > WIDTH - PLAYER_SIZE) player->pos.x = WIDTH - PLAYER_SIZE;
    if (player->pos.x < PLAYER_SIZE) player->pos.x = PLAYER_SIZE;
    if (player->pos.y < PLAYER_SIZE) player->pos.y = PLAYER_SIZE;
    if (player->pos.y > HEIGHT - PLAYER_SIZE) player->pos.y = HEIGHT - PLAYER_SIZE;
    return;
}

/*
*******************
DISEGNO
*******************
*/

void DrawPlayer(Player player){
    if (player.can_kick){
        DrawCircle(player.pos.x, player.pos.y, PLAYER_SIZE, RAYWHITE);
    } else {
        DrawCircle(player.pos.x, player.pos.y, PLAYER_SIZE, BLACK);
    }
    DrawCircle(player.pos.x, player.pos.y, PLAYER_SIZE - 2, RED);
    return;
}

void DrawBall(Ball ball){
    DrawCircle(ball.pos.x, ball.pos.y, BALL_SIZE, BLACK);
    DrawCircle(ball.pos.x, ball.pos.y, BALL_SIZE - 2, RAYWHITE);
    return;
}

void DrawGoals(){
    float x_disp = 100.0;
    float y_disp = 110.0;
    DrawLineEx((Vector2){x_disp, HEIGHT/2 - y_disp}, (Vector2){x_disp/2.0, HEIGHT/2 - y_disp}, 2, BLACK);
    DrawLineEx((Vector2){x_disp/2.0, HEIGHT/2 - y_disp}, (Vector2){x_disp/2.0, HEIGHT/2 + y_disp}, 2, BLACK);
    DrawLineEx((Vector2){x_disp/2.0, HEIGHT/2 + y_disp}, (Vector2){x_disp, HEIGHT/2 + y_disp}, 2, BLACK);
    DrawLineEx((Vector2){WIDTH - x_disp, HEIGHT/2 - y_disp}, (Vector2){WIDTH - x_disp/2.0, HEIGHT/2 - y_disp}, 2, BLACK);
    DrawLineEx((Vector2){WIDTH - x_disp/2.0, HEIGHT/2 - y_disp}, (Vector2){WIDTH - x_disp/2.0, HEIGHT/2 + y_disp}, 2, BLACK);
    DrawLineEx((Vector2){WIDTH - x_disp/2.0, HEIGHT/2 + y_disp}, (Vector2){WIDTH - x_disp, HEIGHT/2 + y_disp}, 2, BLACK);
    return;
}


int main(void){
    Player player1;
    Ball ball;
    InitPlayer(&player1);
    InitBall(&ball);
    InitWindow(WIDTH, HEIGHT, "Haxball Clone");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        UpdatePlayer1(&player1);
        BeginDrawing();
            ClearBackground(DARKGREEN);
            DrawPlayer(player1);
            DrawBall(ball);
            DrawGoals();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
