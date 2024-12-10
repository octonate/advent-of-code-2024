#include <stdio.h>
#include <stdlib.h>
#include "../helpers.c"

#define LINE_LEN 256
#define BUF_SIZE 128
#define GRID_SIDE_LEN 130

Point getGuardPos(char (*grid)[], int gridSideLen) {
    for (int y = 0; y < gridSideLen; y++) {
        for (int x = 0; x < gridSideLen; x++) {
            if ((*grid)[y * gridSideLen + x] == '^') {
                return (Point) { x, y };
            }
        }
    }
    return (Point) { -1, -1 };
}

char getObjAtPoint(char (*grid)[], int gridSideLen, Point pos) {
    if (isPointInGrid(pos, gridSideLen) == false) return 0;

    return (*grid)[pos.y * gridSideLen + pos.x];
}

void turnRight(enum Direction *dir) {
    *dir = (*dir + 1) % 4;
}

void moveForward(Point *guardPos, enum Direction dir) {
    switch (dir) {
    case UP:
        guardPos->y--;
        break;
    case DOWN:
        guardPos->y++;
        break;
    case RIGHT:
        guardPos->x++;
        break;
    case LEFT:
        guardPos->x--;
        break;
    }
}

char getNextObj(char (*grid)[], int gridSideLen, Point guardPos, enum Direction guardDir) {
    char nextObj = 0;
    switch (guardDir) {
    case UP:
        if (guardPos.y == 0) break;
        nextObj = getObjAtPoint(grid, gridSideLen, (Point){ guardPos.x, guardPos.y - 1 });
        break;
    case DOWN:
        if (guardPos.y == gridSideLen - 1) break;
        nextObj = getObjAtPoint(grid, gridSideLen, (Point){ guardPos.x, guardPos.y + 1 });
        break;
    case RIGHT:
        if (guardPos.x == gridSideLen - 1) break;
        nextObj = getObjAtPoint(grid, gridSideLen, (Point){ guardPos.x + 1, guardPos.y });
        break;
    case LEFT:
        if (guardPos.x == 0) break;
        nextObj = getObjAtPoint(grid, gridSideLen, (Point){ guardPos.x - 1, guardPos.y });
        break;
    }

    return nextObj;
}

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    char grid[GRID_SIDE_LEN][GRID_SIDE_LEN];
    int covered[GRID_SIDE_LEN][GRID_SIDE_LEN] = {0};
    int curRow = 0;
    while (fgets(line, sizeof(line), fp)) {
        Str lineStr = strMake(line);
        strncpy(grid[curRow], lineStr.data, GRID_SIDE_LEN);
        curRow++;
    }

    enum Direction guardDir = UP;
    Point guardPos = getGuardPos(grid, GRID_SIDE_LEN);

    for (;;) {
        covered[guardPos.y][guardPos.x] = 1;
        char nextObj = getNextObj(grid, GRID_SIDE_LEN, guardPos, guardDir);
        if (nextObj == 0) break;
        if (nextObj == '#') {
            turnRight(&guardDir);
        }
        moveForward(&guardPos, guardDir);
    }
    printf("PART 1: %d\n", arrCountInts((int *)covered, GRID_SIDE_LEN * GRID_SIDE_LEN, 1));


    fclose(fp);
    return 0;
}
