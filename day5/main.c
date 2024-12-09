#include <stdio.h>
#include "../helpers.c"

#define LINE_LEN 256


typedef struct Rule {
    int before;
    int after;
} Rule;

typedef struct Page {
    int nums[32];
    int numsLen;
} Page;

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    Rule rules[2096];
    int rulesCount = 0;
    bool isRuleTime = true;

    Page pages[512];
    int pagesCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        Str lineStr = strMake(line);
        if (strCompare(lineStr, strMake("\n"))) {
            isRuleTime = false;
            continue;
        }
        if (isRuleTime) {
            int num1 = strToI(splitFirstTok(&lineStr, '|'));
            int num2 = strToI(lineStr);
            rules[rulesCount] = (Rule) { num1, num2 };
            rulesCount++;
            continue;
        }

        Page curPage = { .numsLen = 0 };
        while(1) {
            Str tok = splitFirstTok(&lineStr, ',');
            curPage.nums[curPage.numsLen] = strToI(tok.data == NULL ? lineStr : tok);
            curPage.numsLen++;
            if (tok.data == NULL) break;
        }

        bool isCurPageInOrder = true;
        for (int i = 0; i < rulesCount; i++) {
            int beforeIdx = arrGetIdx(curPage.nums, curPage.numsLen, rules[i].before);
            int afterIdx = arrGetIdx(curPage.nums, curPage.numsLen, rules[i].after);
            if (beforeIdx != -1 && afterIdx != -1 && afterIdx < beforeIdx) {
                isCurPageInOrder = false;
                break;
            }
        }
        if (isCurPageInOrder) {
            pages[pagesCount] = curPage;
            pagesCount++;
        }
    }

    //for (int i = 0; i < rulesCount; i++) {
    //    printf("%d|%d\n", rules[i].before, rules[i].after);
    //}

    //for (int i = 0; i < pagesCount; i++) {
    //    arrPrint(pages[i].nums, pages[i].numsLen, HOR);
    //}

    int sum = 0;
    for (int i = 0; i < pagesCount; i++) {
        sum += pages[i].nums[pages[i].numsLen / 2];
    }

    printf("PART 1: %d\n", sum);


    fclose(fp);
    return 0;
}
