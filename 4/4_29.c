#include <stdio.h>
#include <stdlib.h>

#define INITSTRLEN 100

typedef struct {
    char *ch;   //若是非空串，则按串长度+1分配存储区
    int length; //串长
} HString; 

int StrIndexKMP(HString *s, HString *t, int pos);
void GetNextVal(HString *pattern,int nextval[]);

int main() {
    HString s, t;
    scanf("%d", &s.length);
    scanf("%d", &t.length);
    
    s.ch = (char *)malloc((s.length + 1) * sizeof(char));
    t.ch = (char *)malloc((t.length + 1) * sizeof(char));

    scanf("%s", s.ch);
    scanf("%s", t.ch);
    s.ch[s.length] = '\0'; 
    t.ch[t.length] = '\0'; 

    int pos = 1;
    int index = StrIndexKMP(&s, &t, pos);
    if (index) {
        printf("%d\n", index - 1);
    } else {
        printf("-1\n");
    }
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
        //返回s中与t匹配的子序列第一个字符的序号
    else 
        return 0; //走到主串末尾，匹配失败
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


