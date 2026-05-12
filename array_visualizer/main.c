#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define ARR_LENGTH 10

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

void DrawBars(i32 array[], i32 length){
    i32 width = floorf((float) WIDTH / (float) length);
    i32 height;
    for (i32 i = 0; i < length; i++){
        height = 10 * array[i];
        DrawRectangle(i * width, HEIGHT - height, width, height, RAYWHITE);
        DrawLine((i + 1) * width, HEIGHT, (i + 1) * width, HEIGHT - height, BLACK);
    }
    return;
}

void DrawFinalBars(i32 array[], i32 length){
    struct timespec ts1, ts2;
    ts1.tv_sec = 0; //numero di secondi per cui dormire
    ts1.tv_nsec = 250000000; //numero di nanosecondi per cui dormire
    i32 width = floorf((float) WIDTH / (float) length);
    i32 height;
    for (i32 i = 0; i < length; i++){
        height = 10 * array[i];
        DrawRectangle(i * width, HEIGHT - height, width, height, GREEN);
        DrawLine((i + 1) * width, HEIGHT, (i + 1) * width, HEIGHT - height, BLACK);
        nanosleep(&ts1, &ts2);
    }
    return;
}


int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void InsertionSort(i32 *arr, i32 n)
{
    struct timespec ts1, ts2;
    ts1.tv_sec = 1; //numero di secondi per cui dormire
    ts1.tv_nsec = 0; //numero di nanosecondi per cui dormire
    i32 j;
    i32 key;
    for (i32 i = 1; i < n; ++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            BeginDrawing();
                ClearBackground(BLACK);
                DrawBars(arr, n);
            EndDrawing();
            arr[j + 1] = arr[j];
            j = j - 1;
            nanosleep(&ts1, &ts2);
        }
        arr[j + 1] = key;
    }
    return;
}

void func(i32 **array, i32 length){
    //qsort(*array, length, sizeof(*array[0]), comp);
    InsertionSort(*array, length);
    BeginDrawing();
        DrawFinalBars(*array, length);
    EndDrawing();
    return;
}

void SortArray(i32 **array, void func(i32**, i32)){
    //ci sono qsort, mergesort, heapsort
    func(array, ARR_LENGTH);
    return;
}


int main(void){
    InitWindow(WIDTH, HEIGHT, "Array Visualizer");
    SetTargetFPS(1);
    i32 *arr;
    arr = malloc(ARR_LENGTH * sizeof(i32));
    for (int i = 0; i < ARR_LENGTH; i++){
        arr[i] = arc4random_uniform(10);
    }

    
    while (!WindowShouldClose()){
        SortArray(&arr, func);
    }
    CloseWindow();
    

    free(arr);
    return 0;
}
