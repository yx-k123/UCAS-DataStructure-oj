#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OLNode{
	int i, j;
	int num;
    struct OLNode *right, *down;
} OLNode, *Olink;

typedef struct{
	Olink *rhead, *chead;
	int mu, nu, tu;
} CrossList;

void init(CrossList *A, int m, int n);
void insert(CrossList *A, int row, int col, int num);
void inputVB(CrossList *A, int m, int n);
void add(CrossList *A, CrossList *B, CrossList *C);
void outputVB(CrossList *C);

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    getchar();

    CrossList A, B, C;
    init(&A, m, n);
    init(&B, m, n);
    init(&C, m, n);
    inputVB(&A, m, n);
    inputVB(&B, m, n);

    add(&A, &B, &C);

    outputVB(&C);

    return 0;
}

void init(CrossList *A, int m, int n) {
    A->mu = m;
    A->nu = n;
    A->tu = 0;
    A->rhead = (Olink *)malloc(m * sizeof(Olink));
    A->chead = (Olink *)malloc(n * sizeof(Olink));
    for (int i = 0; i < m; i++) A->rhead[i] = NULL;
    for (int j = 0; j < n; j++) A->chead[j] = NULL;
}

void insert(CrossList *A, int row, int col, int num)
{
    if(num == 0) return;
    OLNode *newnode = (OLNode*)malloc(sizeof(OLNode));
    newnode->i = row;
    newnode->j = col;
    newnode->num = num;
    newnode->down = NULL;
    newnode->right = NULL;

    // insert to row list
    if(A->rhead[row] == NULL || A->rhead[row]->j > col) {
        newnode->right = A->rhead[row];
        A->rhead[row] = newnode;
    } else {
        Olink p = A->rhead[row];
        while(p->right && p->right->j < col) {
            p = p->right;
        }
        newnode->right = p->right;
        p->right = newnode;
    }

    // insert to col list
    if(A->chead[col] == NULL || A->chead[col]->i > row) {
        newnode->down = A->chead[col];
        A->chead[col] = newnode;
    } else {
        Olink q = A->chead[col];
        while(q->down && q->down->i < row) {
            q = q->down;
        }
        newnode->down = q->down;
        q->down = newnode;
    }

    A->tu++;
}

void inputVB(CrossList *A, int m, int n) {
    char line[10000];
    int *V = (int*)malloc(m * n * sizeof(int));
    int *B = (int*)malloc(m * n * sizeof(int));
    int vlen = 0;

    // read V
    fgets(line, sizeof(line), stdin);
    if (line[0] != '\n') {
        char *token = strtok(line, " \n");
        while (token) {
            V[vlen++] = atoi(token);
            token = strtok(NULL, " \n");
        }
    }

    // read B
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &B[i]);
    }
    getchar(); // \n

    // insert
    int idx = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (B[i * n + j]) {
                insert(A, i, j, V[idx++]);
            }
        }
    }
    free(V); free(B);
}

void add(CrossList *A, CrossList *B, CrossList *C) {
    init(C, A->mu, A->nu);
    // insert A
    for (int i = 0; i < A->mu; i++) {
        for (OLNode *p = A->rhead[i]; p; p = p->right) {
            insert(C, p->i, p->j, p->num);
        }
    }
    // insert B
    for (int i = 0; i < B->mu; i++) {
        for (OLNode *p = B->rhead[i]; p; p = p->right) {
            // if in C, add
            OLNode *q = C->rhead[p->i];
            OLNode *prev = NULL;
            while (q && q->j < p->j) {
                prev = q;
                q = q->right;
            }
            if (q && q->j == p->j) {
                q->num += p->num;
                if (q->num == 0) { // add result is 0
                    // delete row
                    if (prev) prev->right = q->right;
                    else C->rhead[p->i] = q->right;
                    // delete col
                    OLNode *colprev = NULL, *colp = C->chead[p->j];
                    while (colp && colp != q) {
                        colprev = colp;
                        colp = colp->down;
                    }
                    if (colprev) colprev->down = q->down;
                    else C->chead[p->j] = q->down;
                    free(q);
                    C->tu--;
                }
            } else {
                insert(C, p->i, p->j, p->num);
            }
        }
    }
}

void outputVB(CrossList *C) {
    int m = C->mu, n = C->nu;
    int *V = (int*)malloc(m * n * sizeof(int));
    int *B = (int*)malloc(m * n * sizeof(int));
    int idx = 0;
    for (int i = 0; i < m * n; i++) B[i] = 0;
    for (int i = 0; i < m; i++) {
        for (OLNode *p = C->rhead[i]; p; p = p->right) {
            V[idx++] = p->num;
            B[p->i * n + p->j] = 1;
        }
    }
    // print V
    for (int i = 0; i < idx; i++) {
        printf("%d", V[i]);
        if (i < idx - 1) printf(" ");
    }
    printf("\n");
    // print B
    for (int i = 0; i < m * n; i++) {
        printf("%d", B[i]);
        if ((i + 1) % n == 0) printf("\n");
        else printf(" ");
    }
    free(V); free(B);
}
