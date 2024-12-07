/* I did some grepping to make the input file easier to read fyi sorry if thats cheating or whatever too bad
 *
 * The grep commands in question are:
 *
 * PART 1:
 * grep -oE 'mul\(.{1,3},.{1,3}\)' inputCorrupted.txt > input.txt
 * sed -i 's/,/ /;s/mul(//;s/)//' input.txt
 *
 *
 */


#include <stdio.h>
#include "../helpers.c"

#define LINE_LEN 32

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    int sum = 0;

    while (fgets(line, sizeof(line), fp)) {
        Str lineStr = strMake(line);
        int num1 = strToI(splitFirstTok(&lineStr, ' '));
        int num2 = strToI(lineStr);

        sum += num1 * num2;
    }

    printf("PART 1: %d\n", sum);

    fclose(fp);
    return 0;
}
