#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void){
    int safe_num = 50;
    int count = 0;
    FILE *file = fopen("ex1_input.txt", "r");
    char line[10];
    bzero(line, 10);
    while (fgets(line, 10, file) != NULL){
        char dir = line[0];
        char nums[4];
        bzero(nums, 4);
        for (int i = 1; i < 6; i++){
            if (isdigit(line[i])){
                nums[i-1] = line[i];
            } else {
                nums[i-1] = '\0';
            }
        }
        int rot = atoi(nums);
        if (dir == 'R') {
            safe_num = (safe_num + rot) % 100;
        } else {
            safe_num = (safe_num - rot) % 100;
        }
        if (safe_num == 0){
            ++count;
        }
    }
    printf("%d\n", count);
}