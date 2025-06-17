#include <stdio.h>

int main()
{
	int array[100] = {0};
	char ch;
    int count = 0;
    while (scanf("%d%c", &array[count], &ch) == 2) {
        count++;
        if (ch == '\n') {
            break;
        }
    }

    int max, min;
    scanf("%d %d", &min, &max);

    for (int i = 0; i < count; i++) {
        if (array[i] > min && array[i] < max) {
            if (i == 0 || array[i] != array[i - 1]) {
                printf("%d ", array[i]);
            }
        }
    }
}