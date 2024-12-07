#include <stdio.h>
#include "../helpers.c"

#define LINE_LEN 32
#define MAX_LEVELS 8

bool isSafe(int arr[], int arrLen) {
    if (arrLen < 2) return true;

    bool isIncr = arr[0] < arr[1] ? true : false;

    for (int i = 0; i < arrLen - 1; i++) {
        if (arr[i] == arr[i + 1]) return false;
        if (arr[i] > arr[i + 1] && isIncr == true) return false;
        if (arr[i] < arr[i + 1] && isIncr == false) return false;
        if (abs(arr[i] - arr[i + 1]) > 3) return false;
    }
    return true;
}

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    int arr[MAX_LEVELS];
    int safeCount = 0;

    while (fgets(line, sizeof(line), fp)) {

        Str lineStr = strMake(line);
        int arrLen = 0;
        for (int i = 0; i < MAX_LEVELS; i++) {
            Str tok = splitFirstTok(&lineStr, ' ');

            if (tok.data == NULL) {
                arr[i] = strToI(lineStr);
                arrLen = i + 1;
                break;
            }

            arr[i] = strToI(tok);
        }

        if (isSafe(arr, arrLen)) {
            safeCount++;
        }
    }

    printf("PART 1: %d\n", safeCount);


    fclose(fp);
    return 0;
}
