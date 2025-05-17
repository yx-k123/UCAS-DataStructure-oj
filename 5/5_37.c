#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {ATOM, LIST} ElemTag;
typedef struct GLNode {	
    ElemTag tag; // ATOM or LIST
    union { 
        char atom;	          
        struct GLNode *hp;
    } data;
    struct GLNode *tp;
} Glist;

Glist *CreateGList(char **str);
Glist* DeleteX(Glist *L, char x);
void PrintGList(Glist *L);
void FreeGList(Glist *L);
int isEmpty(Glist *L) {
    return L == NULL;
}

int main() {
    char input[1000], x;
    
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if (input[len-1] == '\n') input[len-1] = '\0';

    char str[1000];
    sscanf(input, "%s %c", str, &x);

    char *p = str;
    Glist *L = CreateGList(&p);

    L = DeleteX(L, x);

    if (isEmpty(L)) {
        printf("-1\n");
    } else {
        PrintGList(L);
        printf("\n");
    }
    FreeGList(L);
    return 0;
}

Glist *CreateGList(char **str)
{
    if (**str == '\0' || **str == ')' || **str == ',') {
        return NULL;
    }
    Glist *head = NULL, *tail = NULL;
    while (**str && **str != ')') {
        Glist *node = (Glist *)malloc(sizeof(Glist));
        node->tp = NULL;
        if (**str == '(') {
            node->tag = LIST;
            (*str)++; 
            node->data.hp = CreateGList(str);
            if (**str == ')') (*str)++; 
        } else {
            node->tag = ATOM;
            node->data.atom = **str;
            (*str)++;
        }
        if (head == NULL) head = tail = node;
        else { tail->tp = node; tail = node; }
        if (**str == ',') (*str)++;
    }
    return head;
}

Glist* DeleteX(Glist *L, char x) {
    if (!L) return NULL;
    
    if (L->tag == ATOM) {
        if (L->data.atom == x) {
            Glist *next = L->tp;
            free(L);
            return DeleteX(next, x);
        }
        L->tp = DeleteX(L->tp, x);
        return L;
    }
    else { 
        L->data.hp = DeleteX(L->data.hp, x);
        L->tp = DeleteX(L->tp, x);
        
        if (L->data.hp == NULL) {
            Glist *next = L->tp;
            free(L);
            return DeleteX(next, x);
        }
        return L;
    }
}

void PrintGList(Glist *L) {
    if (!L) return;
    
    Glist *p = L;
    int first = 1;
    
    while (p) {
        if (!first) printf(",");
        first = 0;
        
        if (p->tag == ATOM) {
            printf("%c", p->data.atom);
        }
        else {
            printf("(");
            PrintGList(p->data.hp);
            printf(")");
        }
        p = p->tp;
    }
}

void FreeGList(Glist *L) {
    while (L) {
        Glist *next = L->tp;
        if (L->tag == LIST) FreeGList(L->data.hp);
        free(L);
        L = next;
    }
}