#include <stdio.h>
#include "../helpers.c"

#define LINE_LEN 256
#define GRID_WIDTH 140
#define GRID_HEIGHT 140

int xmasCheck(Str str) {
    return strCompare(str, strMake("XMAS")) + strCompare(str, strMake("SAMX"));
}

int masCheck(Str str) {
    return strCompare(str, strMake("MAS")) + strCompare(str, strMake("SAM"));
}


int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }
    
    char grid[GRID_HEIGHT][GRID_WIDTH];

    int row = 0;
    while (fgets(line, sizeof(line), fp)) {
        for (int i = 0; i < GRID_WIDTH; i++) {
            grid[row][i] = line[i];
        }
        row++;
    }

    int sum = 0;
    //search horizontally
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH - 3; j++) {
            Str curStr = strMake((const char []){ grid[i][j], grid[i][j + 1], grid[i][j + 2], grid[i][j + 3], 0 });
            sum += xmasCheck(curStr);
        }
    }

    //search vertically
    for (int i = 0; i < GRID_HEIGHT - 3; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            Str curStr = strMake((const char []){ grid[i][j], grid[i + 1][j], grid[i + 2][j], grid[i + 3][j], 0 });
            sum += xmasCheck(curStr);
        }
    }

    //search diagonally
    for (int i = 0; i < GRID_HEIGHT - 3; i++) {
        for (int j = 0; j < GRID_WIDTH - 3; j++) {
            Str curStr1 = strMake((const char []){ grid[i][j], grid[i + 1][j + 1], grid[i + 2][j + 2], grid[i + 3][j + 3], 0 });
            Str curStr2 = strMake((const char []){ grid[i + 3][j], grid[i + 2][j + 1], grid[i + 1][j + 2], grid[i][j + 3], 0 });
            sum += xmasCheck(curStr1) + xmasCheck(curStr2);
        }
    }
    printf("PART 1: %d\n", sum);


    int sum2 = 0;
    for (int i = 0; i < GRID_HEIGHT - 2; i++) {
        for (int j = 0; j < GRID_WIDTH - 2; j++) {
            Str str1 = strMake((const char[]){ grid[i + 0][j + 0], grid[i + 1][j + 1], grid[i + 2][j + 2], 0 });
            Str str2 = strMake((const char[]){ grid[i + 0][j + 2], grid[i + 1][j + 1], grid[i + 2][j + 0], 0 });
            sum2 += masCheck(str1) && masCheck(str2);
        }
    }

    printf("PART 2: %d\n", sum2);

    fclose(fp);
    return 0;
}
