/* I did some grepping to make the input file easier to read fyi sorry if thats cheating or whatever too bad
 *
 * The grep commands in question are:
 *
 * PART 1:
 * grep -oE "mul\(.{1,3},.{1,3}\)" inputCorrupted.txt > input.txt
 * sed -i "s/,/ /;s/mul(//;s/)//" input.txt
 *
 * PART 2:
 * grep -oE "mul\(.{1,3},.{1,3}\)|do\(\)|don't\(\)" inputCorrupted.txt > input2.txt
 * sed -i "s/,/ /;s/mul(//;s/)//;s/(//" input2.txt
 *
 */


#include <stdio.h>
#include "../helpers.c"

#define LINE_LEN 256

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

    FILE *fp2;
    if ((fp2 = fopen("input2.txt", "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    int sum2 = 0;
    bool enabled = true;

    while (fgets(line, sizeof(line), fp2)) {
        Str lineStr = splitFirstTok(&(Str){ strMake(line).data, strMake(line).len }, '\n');

        if (strCompare(strMake("do"), lineStr)) {
            enabled = true;
            continue;
        } 
        if (strCompare(strMake("don't"), lineStr)) {
            enabled = false;
            continue;
        }

        if (enabled) {
            int num1 = strToI(splitFirstTok(&lineStr, ' '));
            int num2 = strToI(lineStr);

            sum2 += num1 * num2;
        }
    }

    printf("PART 2: %d\n", sum2);

    fclose(fp);
    fclose(fp2);
    return 0;
}
