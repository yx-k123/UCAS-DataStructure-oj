#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSTRLEN 100

typedef struct {
    char *ch;   
    int length; 
} HString; 

int StrIndexKMP(HString *s, HString *t, int pos);
void GetNextVal(HString *pattern,int nextval[]);
int SearchLongestSubstring(HString *s, HString *t);

int main()
{
    HString s;
    HString t;
    
    s.ch = (char *)malloc((INITSTRLEN) * sizeof(char));
    t.ch = (char *)malloc((INITSTRLEN) * sizeof(char));

    scanf("%s", s.ch);
    s.length = strlen(s.ch);
    s.ch[s.length] = '\0';

    int n = SearchLongestSubstring(&s, &t);
    if (n != -1) {
        printf("%s ", t.ch);
    }
    printf("%d\n", n);
    free(s.ch);
    free(t.ch);
    return 0;
}


int StrIndexKMP(HString *s, HString *t, int pos) {
    int next[INITSTRLEN]; 
    GetNextVal(t, next);
    int i,j; 
    i=pos-1; j=0; 
    while(i<s->length && j<t->length)
        if( j== -1 || s->ch[i] == t->ch[j]) 
        {
            i++; 
            j++;
        } else 
            j=next[j];
    if(j>=t->length) 
        return i - t->length + 1;
    else 
        return 0; 
}

void GetNextVal(HString *pattern,int nextval[]){ 
    int j,k;  
    j = 0;
    k = -1; 
    nextval[0]= -1;
    while(j<pattern->length) {
        if(k== -1 || pattern->ch[j] == pattern->ch[k]){
            j++;k++;
            if(pattern->ch[j] == pattern->ch[k]) 		
                nextval[j]=nextval[k];
            else nextval[j]=k;
        } else 
            k=nextval[k];
    }
}

int SearchLongestSubstring(HString *s, HString *t) {
    int maxLen = 0, firstPos = -1;
    for (int len = s->length - 1; len > 0; len--) {
        for (int i = 0; i <= s->length - len; i++) {
            strncpy(t->ch, s->ch + i, len);
            t->ch[len] = '\0';
            t->length = len;
            int pos = StrIndexKMP(s, t, i + 2); 
            if (pos != 0) {
                if (len > maxLen || (len == maxLen && i < firstPos)) {
                    maxLen = len;
                    firstPos = i;
                }
            }
        }
        if (maxLen > 0) 
            break; 
    }
    if (maxLen > 0) {
        strncpy(t->ch, s->ch + firstPos, maxLen);
        t->ch[maxLen] = '\0';
        t->length = maxLen;
        return firstPos;
    }
    return -1;
}