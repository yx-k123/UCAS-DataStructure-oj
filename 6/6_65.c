#include <stdio.h>

void postOrder(char pre[], char in[], int n);

int main()
{
    char precedent_sequence[100], Intermediate_sequences[100];
    int count_precedent, count_intermediate;
    count_precedent = 0;
    count_intermediate = 0;
    char c;
    while(scanf("%c", &c) )
    {
        if (c == '\n') break;
        precedent_sequence[count_precedent] = c;
        count_precedent++;
    }

    while(scanf("%c", &c) )
    {
        if (c == '\n') break;
        Intermediate_sequences[count_intermediate] = c;
        count_intermediate++;
    }

    postOrder(precedent_sequence, Intermediate_sequences, count_precedent);
    printf("\n");
    
    return 0;
}

void postOrder(char pre[], char in[], int n) {
    if (n == 0) return;
    char root = pre[0];
    int i;
    for (i = 0; i < n; i++) {
        if (in[i] == root) break;
    }
    postOrder(pre + 1, in, i);
    postOrder(pre + 1 + i, in + i + 1, n - i - 1);
    printf("%c", root);

    return;
}