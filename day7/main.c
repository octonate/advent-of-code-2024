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

void printBitmask(uint16_t bitmask, int numBits) {
    for (int i = 0; i < numBits; i++) {
        printf("%d", (bitmask & 1 << i) >> i);
    }
}

int64_t arrSum(int nums[], int numsLen) {
    int64_t sum = 0;
    for (int i = 0; i < numsLen; i++) {
        sum += nums[i];
    }
    return sum;
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

int countDigits(int64_t num) {
    return (int) floorl(log10l(num)) + 1;
}

int64_t int64Concat(int64_t num1, int64_t num2) {
    //printf("counddigitsnum2: %d\n", countDigits(num2));
    return num1 * (int64_t) powl(10.0l, countDigits(num2)) + num2;
}

int64_t arrConcat(int nums[], int numsLen) {
    int64_t result = nums[0];
    for (int i = 0; i < numsLen - 1; i++) {
        result = int64Concat(result, nums[i + 1]);
    }
    return result;
}

int64_t evalWithBitmaskBase3(int nums[], int numsLen, uint32_t bitmask) {
    int64_t result = nums[0];
//    printf("%d", nums[0]);

    for (int i = 0; i < numsLen - 1; i++) {
        switch ((int)(bitmask / powl(3, i)) % 3) {
        case 0:
//            printf(" x ");
            result *= nums[i + 1];
            break;
        case 1:
//            printf(" + ");
            result += nums[i + 1];
            break;
        case 2:
//            printf(" || ");
            result = int64Concat(result, nums[i + 1]);
            break;
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
    int64_t sum2 = 0;

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
        if (arrSum(nums, numsLen) > value) continue;

        for (uint16_t i = 0; i < pow(2, numsLen - 1); i++) {
            if (evalWithBitmask(nums, numsLen, i) == value) {
                sum += value;
                break;
            }
        }

        uint32_t maxBitmaskBase3 = pow(3, numsLen - 1);
        if (arrConcat(nums, numsLen) < value) continue;

        for (uint32_t i = 0; i < maxBitmaskBase3; i++) {
            int64_t eval = evalWithBitmaskBase3(nums, numsLen, i);
            if (eval == value) {
                sum2 += value;
                break;
            }
        }
    }

    printf("PART 1: %ld\n", sum);
    printf("PART 2: %ld\n", sum2);

    fclose(fp);
    return 0;
}
