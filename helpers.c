#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define LINE_LEN 32
#define BUF_SIZE 16384

typedef struct Str {
    const char *data;
    int len;
} Str;

int fCountChars(FILE *fp, char ch) {
    char buf[BUF_SIZE];
    int count = 0;

    while (1) {
        size_t curBufLen = fread(buf, sizeof(buf[0]), sizeof(buf), fp);
        if (ferror(fp)) {
            return -1;
        }

        for (int i = 0; i < curBufLen; i++) {
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

Str splitFirstTok(Str *str, char delim) {
    Str out = { .data = str->data };
    bool foundStart = false;

    for (int i = 0; i < str->len; i++) {
        if (str->data[i] != delim) continue;

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
    for (int i = 0; i < str.len; i++) {
        nullstr[i] = str.data[i];
    }
    nullstr[str.len] = 0;
    return atoi(nullstr);
}

void strPrint(Str str) {
    printf("%.*s\n", str.len, str.data);
}

void arrPrint(int arr[], int arrLen) {
    for (int i = 0; i < arrLen; i++) {
        printf("%d\n", arr[i]);
    }
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

int arrCountInts(int arr[], int arrLen, int num) {
    int count = 0;
    for (int i = 0; i < arrLen; i++) {
        if (arr[i] == num) {
            count++;
        }
    }
    return count;
}
