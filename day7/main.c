#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../helpers.c"

#define TEST 0
#define LINE_LEN 256 

#if TEST
    #define INPUT_TXT "test.txt"
    #define LIST_LEN 16
#else
    #define INPUT_TXT "input.txt"
    #define LIST_LEN 1024
#endif
/*
        printf("  ");
        printBitmask(bitmask, numsLen);
        printf("\n& ");
        printBitmask((uint16_t) 1 << i, numsLen);
        printf("\n: ");
        printf("%d\n\n", (bitmask & (1 << i)) > 0);
*/

void printBitmask(uint16_t bitmask, int numBits) {
    for (int i = 0; i < numBits; i++) {
        printf("%d", (bitmask & 1 << i) >> i);
    }
}

int64_t evalWithBitmask(int nums[], int numsLen, uint16_t bitmask) {
    int64_t result = nums[0];
//  printf("%d", nums[0]);


    for (int i = 0; i < numsLen - 1; i++) {
        if ((bitmask & (1 << i)) > 0) {
//            printf(" + ");
            result += nums[i + 1];
        } else {
//            printf(" x ");
            result *= nums[i + 1];
        }
//        printf("%d", nums[i + 1]);
    }
//    printf(" = %ld\n", result);
    return result;
}

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen(INPUT_TXT, "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    int64_t sum = 0;
    int maxNumsLen = 0;

    while (fgets(line, sizeof(line), fp)) {
        Str lineStr = strMake(line);
        int64_t value = strToLL(splitFirstTok(&lineStr, ':'));
        int nums[LIST_LEN] = {0};
        int numsLen = 0;
        Str tok = splitFirstTok(&lineStr, ' ');
        while (1) {
            tok = splitFirstTok(&lineStr, ' ');
            if (tok.data == NULL) {
                nums[numsLen] = strToI(lineStr);
                numsLen++;
                break;
            }

            nums[numsLen] = strToI(tok);
            numsLen++;
        }

    int64_t testSum = 1;
    for (int i = 0; i < numsLen; i++) {
        testSum *= nums[i];
    }
        for (uint16_t i = 0; i < pow(2, numsLen - 1); i++) {
            if (evalWithBitmask(nums, numsLen, i) == value) {
                sum += value;
                break;
            }
        }

        if (numsLen > maxNumsLen) {
            maxNumsLen = numsLen;
        }
    }

    printf("PART 1: %ld\n", sum);

    fclose(fp);
    return 0;
}
