#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  CHUNKSIZE 8

typedef struct Chunk { 
    char  ch[CHUNKSIZE];
    struct  Chunk * next ;
} Chunk;               

typedef struct { 
    Chunk  *head;         
    Chunk  *tail;            
    int  curLen;              
} LString;   

void InitLString(LString *s, char *str)
{
    s->head = NULL;
    s->tail = NULL;
    s->curLen = 0;

    int length = strlen(str);
    s->curLen = length/CHUNKSIZE;
    if(length % CHUNKSIZE != 0)
        s->curLen++;
    
    s->head = (Chunk *)malloc(sizeof(Chunk));
    s->head->next = NULL;
    s->tail = s->head;

    for (int i = 0; i < s->curLen; i++) {
        int j = 0;
        for (; j < CHUNKSIZE; j++) {
            if (i * CHUNKSIZE + j < length) {
                s->tail->ch[j] = str[i * CHUNKSIZE + j];
            } else {
                s->tail->ch[j] = '#';
            }
        }

        if ( i * CHUNKSIZE + j < length) {
            s->tail->next = (Chunk *)malloc(sizeof(Chunk));
            s->tail = s->tail->next;
            s->tail->next = NULL;
        }
    }

    return;
}

void PrintLString(LString *s)
{
    Chunk *p = s->head;
    while (p != NULL) {
        for (int i = 0; i < CHUNKSIZE; i++) {
            if (p->ch[i] == '#') {
                break;
            }
            printf("%c", p->ch[i]);
        }
        p = p->next;
    }
    printf("\n");
}

void FreeLString(LString *s)
{
    Chunk *p = s->head;
    while (p != NULL) {
        Chunk *temp = p;
        p = p->next;
        free(temp);
    }
}

void IfReverse(LString *s, char *str)
{   
    int length = strlen(str);
    for (int i = 0; i < s->curLen; i++) {
        for (int j = 0; j < CHUNKSIZE; j++) 
        {
            if (s->head->ch[j] == '#') {
                break;
            }
            
            if (s->head->ch[j] != str[length - (i * CHUNKSIZE + j) - 1]) {
                printf("0\n");
                return;
            }
        }
        s->head = s->head->next;
    }
    printf("1\n");
    return;
}

int main()
{   
    int n;
    scanf("%d", &n);
    LString s;
    char str[100];

    scanf("%s", str);
    
    InitLString(&s, str);
    IfReverse(&s, str);
    FreeLString(&s);

    return 0;
}

