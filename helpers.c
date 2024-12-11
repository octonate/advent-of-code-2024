#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define FILE_BUF_SIZE 16384

#define MOVE_CURSOR_RIGHT(x) printf("\033[%dC", x)
#define MOVE_CURSOR_LEFT(x) printf("\033[%dD", x)

typedef struct Point {
    int x;
    int y;
} Point;


typedef struct Str {
    const char *data;
    size_t len;
} Str;


enum Axis {
    HOR,
    VERT
};

enum Direction {
    UP = 1,
    RIGHT,
    DOWN,
    LEFT,
};

enum PrimitiveType {
    TYPE_INT = 0,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_DOUBLE,
};

bool isPointInGrid(Point pos, int gridSideLen) {
    return (pos.x >= 0 
            && pos.y >= 0
            && pos.x < gridSideLen
            && pos.y < gridSideLen);
}

void gridPrintGeneric(void *arr, int width, int height, enum PrimitiveType type) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (type) {
            case TYPE_INT:
                printf("%d", ((int *)arr)[i * width + j]);
                break;
            case TYPE_CHAR:
                printf("%c", ((char *)arr)[i * width + j]);
                break;
            case TYPE_FLOAT:
                printf("%.*f", 3, ((float *)arr)[i * width + j]);
                break;
            case TYPE_DOUBLE:
                printf("%.*lf", 3, ((double *)arr)[i * width + j]);
                break;
            }
        }
        printf("\n");
    }
}


int fCountChars(FILE *fp, char ch) {
    char buf[FILE_BUF_SIZE];
    int count = 0;

    while (1) {
        size_t curBufLen = fread(buf, sizeof(buf[0]), sizeof(buf), fp);
        if (ferror(fp)) {
            return -1;
        }

        for (size_t i = 0; i < curBufLen; i++) {
            if (buf[i] == ch) {
                count++;
            }
        }

        if (feof(fp)) {
            break;
        }
    }

    rewind(fp);
    return count;
}

Str strMake(const char *nullstr) {
    return (struct Str) { .data = nullstr, .len = strlen(nullstr) };
}

bool strCompare(Str str1, Str str2) {
    if (str1.len != str2.len) return false;

    for (size_t i = 0; i < str1.len; i++) {
        if (str1.data[i] != str2.data[i]) {
            return false;
        }
    }
    return true;
}

Str splitFirstTok(Str *str, char delim) {
    Str out = { NULL, 0 };
    bool foundStart = false;

    for (size_t i = 0; i < str->len; i++) {
        if (str->data[i] != delim) continue;

        out = *str;
        if (foundStart == false) {
            out.len = i;
        }

        foundStart = true;
        if (str->data[i + 1] == delim) continue;

        if (i == str->len - 1) {
            str->data = NULL;
            str->len = 0;
        } else {
            str->data += i + 1;
            str->len -= i + 1;
        }
        break;
    }

    return out;
}

int strToI(Str str) {
    char nullstr[str.len + 1];
    for (size_t i = 0; i < str.len; i++) {
        nullstr[i] = str.data[i];
    }
    nullstr[str.len] = 0;
    return atoi(nullstr);
}

long long strToLL(Str str) {
    char nullstr[str.len + 1];
    for (size_t i = 0; i < str.len; i++) {
        nullstr[i] = str.data[i];
    }
    nullstr[str.len] = 0;
    return atoll(nullstr);
}

void strPrint(Str str) {
    printf("%.*s", (int) str.len, str.data);
}

void arrPrint(int arr[], size_t arrLen, enum Axis axis) {
    for (size_t i = 0; i < arrLen; i++) {
        printf("%d%c", arr[i], axis == HOR ? ' ' : '\n');
    }
    printf("\n");
}


void countSort(int arr[], int arrLen) {
    int maxVal = INT_MIN;
    int minVal = INT_MAX;
    for (int i = 0; i < arrLen; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    int countArrLen = maxVal - minVal + 1;
    int countArr[countArrLen];
    memset(countArr, 0, sizeof(countArr));

    for (int i = 0; i < arrLen; i++) {
        countArr[arr[i] - minVal] += 1;
    }

    for (int i = 1; i < countArrLen; i++) {
        countArr[i] += countArr[i - 1];
    }

    int outArr[arrLen];

    for (int i = arrLen - 1; i >= 0; i--) {
        outArr[--countArr[arr[i] - minVal]] = arr[i];
    }

    for (int i = 0; i < arrLen; i++) {
        arr[i] = outArr[i];
    }
}

int arrCountInts(int arr[], size_t arrLen, int num) {
    int count = 0;
    for (size_t i = 0; i < arrLen; i++) {
        if (arr[i] == num) {
            count++;
        }
    }
    return count;
}

size_t arrGetIdx(int arr[], size_t arrLen, int num) {
    for (size_t i = 0; i < arrLen; i++) {
        if (arr[i] == num) {
            return i;
        }
    }
    return (size_t) -1;
}

void arrSwapIdxs(int arr[], size_t arrLen, size_t idx1, size_t idx2) {
    if (idx1 >= arrLen || idx2 >= arrLen) {
        return;
    }
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

