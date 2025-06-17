#include <stdio.h>
#include <stdlib.h>

typedef struct SStable {
    int *u;
    int *v;
    int length;
} SStable;

void initSStable(SStable *stable, int n);
void insertSStable(SStable *stable, int data);
int searchSStable(SStable *stable, int data);

int main()
{
    SStable stable;
    initSStable(&stable, 1000);

    char c;
    int temp;
    while(scanf("%d%c", &temp, &c) != EOF) {
        insertSStable(&stable, temp);
        if (c == '\n') {
            break;
        }
    }

    while(scanf("%d%c", &temp, &c) != EOF) {
        int index = searchSStable(&stable, temp);
        printf("%d", index);
        if (c == '\n') {
            printf("\n");
            break;
        } else {
            printf(" ");
        }
    }

    return 0;
}

void initSStable(SStable *stable, int n)
{
    stable->u = (int *)malloc(n * sizeof(int));
    stable->v = stable->u;
    stable->length = 0;
}

void insertSStable(SStable *stable, int data)
{
    if (stable->length >= 1000) {
        printf("Error: Stable is full.\n");
        return;
    }
    stable->u[stable->length] = data;
    stable->length++;
}

int searchSStable(SStable *stable, int data)
{   
    int *current = stable->v;

    if (*stable->v == data) {
        return 1;
    } else if (*stable->v > data) {
        for (int i = 0; i < current - stable->u; i++) {
            if (stable->u[i] == data) {
                stable->v = stable->u + i;
                return 1; 
            }
        }
    } else {
        for (int i = current - stable->u; i < stable->length; i++) {
            if (stable->u[i] == data) {
                stable->v = stable->u + i;
                return 1;
            }
        }
    }

    return 0;
}