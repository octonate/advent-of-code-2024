#include <stdio.h>
#include "../helpers.c"

#define TEST 0
#define LINE_LEN 256 

#if TEST
    #define INPUT_TXT "test.txt"
#else
    #define INPUT_TXT "input.txt"
#endif

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen(INPUT_TXT, "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
    }

    fclose(fp);
    return 0;
}
