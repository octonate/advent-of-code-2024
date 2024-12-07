#include <stdio.h>
#include "../helpers.c"

int main(void) {
    FILE *fp;
    char line[LINE_LEN];
    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("cant open file bruh\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
    }

    fclose(fp);
    return 0;
}
