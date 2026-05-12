#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>
#include <strings.h>

#define WIDTH 800
#define HEIGHT 800
#define DOTS_PER_FRAME 100


typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


void DrawRandomPoint(RenderTexture2D *canvas){
    BeginTextureMode(*canvas);
        float posx = GetRandomValue(100, 700);
        float posy = GetRandomValue(100, 700);
        if (sqrt((posx - WIDTH/2) * (posx - WIDTH/2) + (posy - HEIGHT/2) * (posy - HEIGHT/2)) > 300){
            DrawPixel(posx, posy, RED);
        }
        else {
            DrawPixel(posx, posy, GREEN);
        }
    EndTextureMode();
}


int main(void){
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "Pi Day!");
    RenderTexture2D canvas = LoadRenderTexture(600, 600);
    char buf[50] = {0};
    u32 total_points = 0;
    u32 points_in_circle = 0;
    SetTargetFPS(60);

    BeginTextureMode(canvas);
        ClearBackground(BLACK);
    EndTextureMode();


    while (!WindowShouldClose()){
        bzero(buf, 50);
        BeginTextureMode(canvas);
            for (int i = 0; i < DOTS_PER_FRAME; i++){
                total_points++;
                float posx = GetRandomValue(0, 600);
                float posy = GetRandomValue(0, 600);
                if (sqrt((posx + 100 - WIDTH/2) * (posx + 100 - WIDTH/2) + (posy + 100 - HEIGHT/2) * (posy + 100 - HEIGHT/2)) > 300){
                    DrawPixel(posx, posy, RED);
                }
                else {
                    DrawPixel(posx, posy, GREEN);
                    points_in_circle++;
                }
            }
        EndTextureMode();


        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureRec(canvas.texture, (Rectangle) {0, 0, (float)canvas.texture.width, (float)-canvas.texture.height},
                           (Vector2) {100.0, 100.0}, RAYWHITE);
            
            DrawPolyLines((Vector2) {WIDTH/2, HEIGHT/2}, 60, 300, 0, RAYWHITE);
            DrawRectangleLines(100, 100, 600, 600, RAYWHITE);
            sprintf(buf, "Pi greco (approssimato): %f", ((float)points_in_circle/(float)total_points)*4.0);
            DrawText(buf, 50, 50, 20, RAYWHITE);
            
        EndDrawing();
    }

    return 0;
}
