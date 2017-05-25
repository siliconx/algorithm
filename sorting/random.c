// @siliconx
// 2017-05-25 14:27:25
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("one intger argument expected\nfor example: `./random 99`\n");
        return 0;
    }
    srand(time(NULL));
    int range = atoi(argv[1]);
    printf("%d\n", range);
    int r = rand() % range;
    for (int i=0; i<range; i++) {
        printf("%d ", r);
        r = rand() % range;
    }
    printf("\n");
    return 0;
}

