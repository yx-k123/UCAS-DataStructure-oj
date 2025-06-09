#include <stdio.h>

void read_data(int *array, int *count);
void inorder(int idx);

int tree_L[100], tree_R[100], insert_L[100], insert_R[100];

int main()
{
    int insert_idx, count_tree_L, count_insert_L, count_tree_R, count_insert_R;
    read_data(tree_L, &count_tree_L);
    read_data(tree_R, &count_tree_R);
    scanf("%d", &insert_idx);
    read_data(insert_L, &count_insert_L);
    read_data(insert_R, &count_insert_R);

    int old_left = tree_L[insert_idx];

    tree_L[insert_idx] = insert_L[0]; 

    for (int i = 1; i < count_insert_L; i++) {
        tree_L[insert_L[0] + i - 1] = insert_L[i];
    }

    for (int i = 1; i < count_insert_R; i++) {
        tree_R[insert_L[0] + i - 1] = insert_R[i];
    }

    tree_R[tree_L[insert_idx]] = old_left;

    inorder(1);
    printf("\n");

    return 0;
}   

void read_data(int *array, int *count)
{   
    int i = 0;
    char c;
    while(scanf("%d%c", &array[i], &c) == 2)
    {
        i++;
        if (c == '\n') break;
    }

    *count = i;
    
    return;
}

void inorder(int idx) {
    if (idx == 0 || idx > 100) return;
    
    if (tree_L[idx] != 0) {
        inorder(tree_L[idx]);
    }
    
    printf("%d ", idx);
    
    if (tree_R[idx] != 0) {
        inorder(tree_R[idx]);
    }
}