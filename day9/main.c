#include <stdio.h>
#include <stdint.h>

#include "../helpers.c"

#define TEST 0

#if TEST
    #define INPUT_TXT "test.txt"
    #define LINE_LEN 19
#else
    #define INPUT_TXT "input.txt"
    #define LINE_LEN 19999
#endif

int main(void) {
    FILE *fp;
    if ((fp = fopen(INPUT_TXT, "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }
    int diskmap[LINE_LEN];

    for (int i = 0; i < LINE_LEN; i++) {
        diskmap[i] = atoi((const char[]){ (const char) fgetc(fp), 0 });
    }

    int diskPos1 = 0;
    int diskPos2 = LINE_LEN - 1;
    int64_t sum = 0;
    int filePos = 0;

    while (diskPos2 >= diskPos1) {
        if (diskPos1 % 2 == 0) {
            for (int i = 0; i < diskmap[diskPos1]; i++) {
                //printf("%ld", diskPos1 / 2);
                sum += (diskPos1 / 2) * filePos;
                filePos++;
            }
        } else {
            for (int i = 0; i < diskmap[diskPos1]; i++) {
                //printf("%ld", diskPos2 / 2);
                sum += (diskPos2 / 2) * filePos;
                filePos++;
                if (--diskmap[diskPos2] == 0) {
                    diskPos2 -= 2;
                }
                if (diskPos2 <= diskPos1) {
                    break;
                }
            }
        }
        diskPos1++;
    }
    //printf("\n");

    printf("PART 1: %ld\n", sum);

    fclose(fp);
    return 0;
}
