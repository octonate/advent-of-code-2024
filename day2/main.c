#include <stdio.h>
#include "../helpers.c"

#define LINE_LEN 32
#define MAX_LEVELS 8

bool isSafe(int arr[], int arrLen) {
    if (arrLen < 2) return true;

    bool isIncr = arr[0] < arr[1] ? true : false;

    for (int i = 0; i < arrLen - 1; i++) {
        if (arr[i] == arr[i + 1]
            || (arr[i] > arr[i + 1] && isIncr == true)
            || (arr[i] < arr[i + 1] && isIncr == false)
            || (abs(arr[i] - arr[i + 1]) > 3)) {
            return false;
        }
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

    int safeCount = 0;
    int dampenedSafeCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        int arr[MAX_LEVELS];
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
            dampenedSafeCount++;
            continue;
        }

        //yuck
        int arrComb[arrLen - 1];
        for (int i = 0; i < arrLen - 1; i++) {
            for (int j = 0; j < arrLen; j++) {
                if (j > i) {
                    arrComb[j - 1] = arr[j];
                } else if (j < i) {
                    arrComb[j] = arr[j];
                }
            }
            if (isSafe(arrComb, arrLen - 1)) {
                dampenedSafeCount++;
            }
        }
    }

    printf("PART 1: %d\n", safeCount);
    printf("PART 2: %d\n", dampenedSafeCount);


    fclose(fp);
    return 0;
}
