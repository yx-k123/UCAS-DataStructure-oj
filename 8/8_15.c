#include <stdio.h>

int main() {
    int lowbound, highbound, cellsize;
    scanf("%d %d %d", &lowbound, &highbound, &cellsize);

    int a;
    int start = lowbound;
    int start1 = lowbound;
    int length = 0;
    int result = 1;
    int rresult = 0;

    while (scanf("%d", &a) != EOF) {
        result = result & a;
        rresult = rresult | a;
        if (a == 0) {
            length += cellsize;
            start1 += cellsize;
        } else if (a == 1) {
            if (length != 0)
                printf("%d %d %d\n", 0, start, length);
            start = start1;
            length = 0;
            start += cellsize;
            start1 += cellsize;
        }
    }

    if (rresult == 0) {
        printf("%d %d %d", 0, lowbound, highbound);
    }
    if (result == 1) {
        printf("0 0 0");
    }

    return 0;
}