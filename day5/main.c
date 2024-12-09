#include <stdio.h>
#include "../helpers.c"

#define LINE_LEN 256
#define LIST_LEN 100
#define BUF_SIZE 2096

typedef struct Rule {
    int before;
    int after;
} Rule;

typedef struct Page {
    int nums[32];
    int numsLen;
} Page;

bool isPageInOrder(Page page, Rule rules[], int rulesLen) {
        for (int i = 0; i < rulesLen; i++) {
            int beforeIdx = arrGetIdx(page.nums, page.numsLen, rules[i].before);
            int afterIdx = arrGetIdx(page.nums, page.numsLen, rules[i].after);
            if (beforeIdx != -1 && afterIdx != -1 && afterIdx < beforeIdx) {
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


    Rule rules[BUF_SIZE];
    int rulesCount = 0;

    Page pages[BUF_SIZE];
    int pagesCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        Str lineStr = strMake(line);
        if (strCompare(lineStr, strMake("\n"))) {
            break;
        }
        int num1 = strToI(splitFirstTok(&lineStr, '|'));
        int num2 = strToI(lineStr);
        rules[rulesCount] = (Rule) { num1, num2 };
        rulesCount++;
    }

    while (fgets(line, sizeof(line), fp)) {
        Str lineStr = strMake(line);
        Page curPage = { .numsLen = 0 };
        while(1) {
            Str tok = splitFirstTok(&lineStr, ',');
            curPage.nums[curPage.numsLen] = strToI(tok.data == NULL ? lineStr : tok);
            curPage.numsLen++;
            if (tok.data == NULL) break;
        }

        pages[pagesCount] = curPage;
        pagesCount++;
    }

    int sum = 0;
    int sum2 = 0;
    for (int i = 0; i < pagesCount; i++) {
        if (isPageInOrder(pages[i], rules, rulesCount)) {
            sum += pages[i].nums[pages[i].numsLen / 2];
        } else {
            /* yikes im sorry */
            for (int j = 0; j < pages[i].numsLen; j++) {
                if (isPageInOrder(pages[i], rules, rulesCount)) break;

                for (int k = 0; k < rulesCount; k++) {
                    int beforeIdx = arrGetIdx(pages[i].nums, pages[i].numsLen, rules[k].before);
                    int afterIdx = arrGetIdx(pages[i].nums, pages[i].numsLen, rules[k].after);
                    if (beforeIdx != -1 && afterIdx != -1 && afterIdx < beforeIdx) {
                        arrSwapIdxs(pages[i].nums, pages[i].numsLen, beforeIdx, afterIdx);
                    }
                }
            }

            sum2 += pages[i].nums[pages[i].numsLen / 2];
        }
    }

    printf("PART 1: %d\n", sum);
    printf("PART 2: %d\n", sum2);

    fclose(fp);
    return 0;
}
