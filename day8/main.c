#include <stdio.h>
#include "../helpers.c"

#define TEST 0
#define LINE_LEN 256 
#define NUM_ANTENNAS 64

#if TEST
    #define INPUT_TXT "test.txt"
    #define GRID_SIDE_LEN 12
#else
    #define INPUT_TXT "input.txt"
    #define GRID_SIDE_LEN 50
#endif

struct PointPair {
    Point point1;
    Point point2;
};

struct PointPair getAntinodes(Point point1, Point point2) {
    return (struct PointPair) {
        { 2 * point2.x - point1.x,
          2 * point2.y - point1.y },
        { -point2.x - 2 * point1.x,
          -point2.y - 2 * point1.y }
    };
}

void getAntinodesUpdated(Point *anodesList, int *anodesListLen, Point point1, Point point2, int gridSideLen) {
    Point curPoint = point1;
    int dx = point2.x - point1.x;
    int dy = point2.y - point1.y;
    *anodesListLen = 0;
    while (isPointInGrid(curPoint, gridSideLen)) {
        anodesList[*anodesListLen] = curPoint;
        (*anodesListLen)++;
        curPoint.x += dx;
        curPoint.y += dy;
    }
    curPoint = point2;
    while (isPointInGrid(curPoint, gridSideLen)) {
        anodesList[*anodesListLen] = curPoint;
        (*anodesListLen)++;
        curPoint.x += dx;
        curPoint.y += dy;
    }
}

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen(INPUT_TXT, "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    Point antennas[CHAR_MAX][NUM_ANTENNAS];
    int antIdxs[CHAR_MAX];
    int antIdxsLen = 0;
    int freqLens[CHAR_MAX] = {0};

    int antinodeGrid[GRID_SIDE_LEN][GRID_SIDE_LEN] = {0};
    int antinodeGridUpdated[GRID_SIDE_LEN][GRID_SIDE_LEN] = {0};

    for (int i = 0; i < GRID_SIDE_LEN; i++) {
        fgets(line, sizeof(line), fp);

        for (int j = 0; j < GRID_SIDE_LEN; j++) {
            if (line[j] != '.') {
                int charIdx = (int) line[j];
                antennas[charIdx][freqLens[charIdx]] = (Point) { j, i };
                freqLens[charIdx]++;
            }
        }
    }
    for (int i = 0; i < CHAR_MAX; i++) {
        if (freqLens[i] > 0) {
            antIdxs[antIdxsLen] = i;
            antIdxsLen++;
        }
    }

    for (int i = 0; i < antIdxsLen; i++) {
        int curAntennaType = antIdxs[i];
        for (int j = 0; j < freqLens[curAntennaType]; j++) {
            Point point1 = antennas[curAntennaType][j];

            for (int k = 0; k < freqLens[curAntennaType]; k++) {
                Point point2 = antennas[curAntennaType][k];
                if (pointCompare(point1, point2)) continue;

                struct PointPair antinodes = getAntinodes(point1, point2);
                if (isPointInGrid(antinodes.point1, GRID_SIDE_LEN)) {
                    antinodeGrid[antinodes.point1.y][antinodes.point1.x] = 1;
                }
                if (isPointInGrid(antinodes.point2, GRID_SIDE_LEN)) {
                    antinodeGrid[antinodes.point2.y][antinodes.point2.x] = 1;
                }

                Point anodesList[NUM_ANTENNAS];
                int anodesListLen;
                getAntinodesUpdated(anodesList, &anodesListLen, point1, point2, GRID_SIDE_LEN);
                for (int l = 0; l < anodesListLen; l++) {
                    antinodeGridUpdated[anodesList[l].y][anodesList[l].x] = 1;
                }
            }
        }
    }


    //for (int i = 0; i < antIdxsLen; i++) {
    //    printf("%c:\n", antIdxs[i]);
    //    for (int j = 0; j < freqLens[antIdxs[i]]; j++) {
    //        printf("    { %d, %d }\n", antennas[antIdxs[i]][j].x, antennas[antIdxs[i]][j].y);
    //    }
    //}

    int sum = arrCountInts(&antinodeGrid[0][0], GRID_SIDE_LEN * GRID_SIDE_LEN, 1);
    int sum2 = arrCountInts(&antinodeGridUpdated[0][0], GRID_SIDE_LEN * GRID_SIDE_LEN, 1);
    printf("PART 1: %d\n", sum);
    printf("PART 2: %d\n", sum2);

    fclose(fp);
    return 0;
}
