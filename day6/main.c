#include <stdio.h>
#include <stdlib.h>
#include "../helpers.c"

#define TEST 0
#define LINE_LEN 256
#define BUF_SIZE 128

#if TEST
    #define GRID_SIDE_LEN 10
    #define INPUT_TXT "test.txt"
#else 
    #define GRID_SIDE_LEN 130
    #define INPUT_TXT "input.txt"
#endif

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

enum Direction turnRight(enum Direction dir) {
    switch (dir) {
    case UP:
        return RIGHT;
        break;
    case DOWN:
        return LEFT;
        break;
    case RIGHT:
        return DOWN;
        break;
    case LEFT:
        return UP;
        break;
    }
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

Point getNextPoint(char (*grid)[], int gridSideLen, Point guardPos, enum Direction guardDir) {
    Point nextPos;
    switch (guardDir) {
    case UP:
        nextPos = (Point){ guardPos.x, guardPos.y - 1 };
        break;
    case DOWN:
        nextPos = (Point){ guardPos.x, guardPos.y + 1 };
        break;
    case RIGHT:
        nextPos = (Point){ guardPos.x + 1, guardPos.y };
        break;
    case LEFT:
        nextPos = (Point){ guardPos.x - 1, guardPos.y };
        break;
    }

    if (isPointInGrid(nextPos, gridSideLen)) {
        return nextPos;
    } else {
        return (Point){ -1, -1 };
    }
}
int isLoopingExecutions = 0;

bool isLooping(char (*grid)[], int gridSideLen) {
    isLoopingExecutions++;
    //system("clear");
    //gridPrintGeneric(grid, gridSideLen, gridSideLen, TYPE_CHAR);
    //printf("\n%d\n", isLoopingExecutions);

    Point guardPos = getGuardPos(grid, gridSideLen);
    Point initialPos = guardPos;
    enum Direction guardDir = UP;
    //int covered[GRID_SIDE_LEN][GRID_SIDE_LEN][4] = {0};

    (*grid)[guardPos.y * gridSideLen + guardPos.x] = '.';

    for (int i = 0; i < gridSideLen * gridSideLen; i++) {
        moveForward(&guardPos, guardDir);
        //if (covered[guardPos.y][guardPos.x][guardDir] == 1) return true;
        //covered[guardPos.y][guardPos.x][guardDir] = 1;
        Point nextPoint = getNextPoint(grid, GRID_SIDE_LEN, guardPos, guardDir);
        char nextObj = getObjAtPoint(grid, GRID_SIDE_LEN, nextPoint);
        if (nextObj == 0) return false;
        if (nextObj == '#') {
            guardDir = turnRight(guardDir);
        }
    }
    return true;
}

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen(INPUT_TXT, "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    char grid[GRID_SIDE_LEN][GRID_SIDE_LEN];
    int covered[GRID_SIDE_LEN][GRID_SIDE_LEN] = {0};
    int curRow = 0;
    while (fgets(line, sizeof(line), fp)) {
        Str lineStr = strMake(line);
        strncpy(grid[curRow], lineStr.data, GRID_SIDE_LEN);
        strPrint(lineStr);
        curRow++;
    }
    printf("\n");

    enum Direction guardDir = UP;
    Point guardPos = getGuardPos(grid, GRID_SIDE_LEN);
    Point initGuardPos = guardPos;
    int sumLoopObjs = 0;

    for (;;) {
        moveForward(&guardPos, guardDir);
        covered[guardPos.y][guardPos.x] = guardDir;
        Point nextPoint = getNextPoint(grid, GRID_SIDE_LEN, guardPos, guardDir);
        char nextObj = getObjAtPoint(grid, GRID_SIDE_LEN, nextPoint);
        char gridSim[GRID_SIDE_LEN][GRID_SIDE_LEN];

        memcpy(gridSim, grid, sizeof(char) * GRID_SIDE_LEN * GRID_SIDE_LEN);
        gridSim[nextPoint.y][nextPoint.x] = '#';

        if (nextPoint.x != initGuardPos.x && nextPoint.y != initGuardPos.y && nextObj != '#') {
            sumLoopObjs += isLooping(gridSim, GRID_SIDE_LEN);
        }

        if (nextObj == 0) break;
        if (nextObj == '#') {
            guardDir = turnRight(guardDir);
        }

    }

    int sumSpacesCovered = GRID_SIDE_LEN * GRID_SIDE_LEN - arrCountInts((int *)covered, GRID_SIDE_LEN * GRID_SIDE_LEN, 0);
    printf("PART 1: %d\n", sumSpacesCovered);
    printf("PART 2: %d\n", sumLoopObjs);


    fclose(fp);
    return 0;
}
