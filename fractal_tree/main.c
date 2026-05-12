#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600
#define BRANCH_COLOR RAYWHITE
#define THICKNESS 1
#define STARTING_LENGTH 400.0

float ratio = 0.75;
float deltaAngle = 0.2 * PI;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


Vector2 DrawBranch(float x, float y, float length, double angle, float thickness, u8 depth){
    Vector2 start = {x, y};
    float x_end = x + sin(angle) * length * depth/2;
    float y_end = y - cos(angle) * length * depth/2;
    Vector2 end = {x_end, y_end};
    DrawLineEx(start, end, thickness, BRANCH_COLOR);
    return end;
}

void DrawTree(Vector2 start, float length, double angle, float thickness, u8 depth, u8 branches_per_iter){
    if (depth == 0){
        return;
    }
    Vector2 end1 = DrawBranch(start.x, start.y, length, angle, thickness, depth);
    depth -= 1;
    length = length * ratio;
    switch (branches_per_iter){

        case 2:
            DrawTree(end1, length, angle + deltaAngle, thickness, depth, branches_per_iter);
            DrawTree(end1, length, angle - deltaAngle, thickness, depth, branches_per_iter); 
            break;
        
        case 3:
            DrawTree(end1, length, angle + deltaAngle, thickness, depth, branches_per_iter);
            DrawTree(end1, length, angle, thickness, depth, branches_per_iter);
            DrawTree(end1, length, angle - deltaAngle, thickness, depth, branches_per_iter);
            break;

        case 4:
            DrawTree(end1, length, angle + deltaAngle, thickness, depth, branches_per_iter);
            DrawTree(end1, length, angle + deltaAngle/3, thickness, depth, branches_per_iter);
            DrawTree(end1, length, angle - deltaAngle/3, thickness, depth, branches_per_iter);
            DrawTree(end1, length, angle - deltaAngle, thickness, depth, branches_per_iter);
            break;
         
        default:
            DrawTree(end1, length, angle + deltaAngle, thickness, depth, 2);
            DrawTree(end1, length, angle - deltaAngle, thickness, depth, 2); 
            break;
    }
}


int main(int argc, char *argv[]){
    u8 branches = 0;
    u8 depth = 0;
    float length = 0.0;

    switch(argc){
        case 1:
            branches = 2;
            depth = 8;
            break;
        
        case 2:
            branches = (u8) atoi(argv[1]);
            if (branches < 2){
                printf("Ci devono essere almeno 2 rami per intersezione.\n\n\n");
                exit(1);
            } else if (branches > 4){
                printf("Al momento sono supportati max 4 rami per intersezione.\n\n\n");
                exit(1);
            }
            depth = 8;
            break;

        case 3:
            branches = (u8) atoi(argv[1]);
            if (branches < 2){
                printf("Ci devono essere almeno 2 rami per intersezione.\n\n\n");
                exit(1);
            } else if (branches > 4){
                printf("Al momento supporto max 4 rami per intersezione.\n\n\n");
                exit(1);
            }
            depth = (u8) atoi(argv[2]);
            if (depth < 1){
                printf("La profondità deve essere almeno 1.\n\n\n");
                exit(1);
            } else if (depth > 20){
                printf("Profondità troppo alta.\n\n\n");
                exit(1);
            } else if (depth > 15 && branches >= 3){
                printf("Profondità troppo alta.\n\n\n");
                exit(1);
            } else if (depth > 10 && branches == 4){
                printf("Profondità troppo alta.\n\n\n");
                exit(1);
            }
            break;

        default:
            printf("Troppi argomenti, usage: %s numero_rami profondità\n\n\n", argv[0]);
            exit(1);
            break;
    }
    
    length = STARTING_LENGTH * (1.0/ (float) (depth + 1));
    
    InitWindow(WIDTH, HEIGHT, "Fractal Tree");
    SetTargetFPS(1);
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTree((Vector2) {WIDTH/2, HEIGHT - 20}, length, 0, THICKNESS, depth, branches);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
