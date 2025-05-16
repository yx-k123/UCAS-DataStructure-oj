#include <stdio.h>
#include <string.h>

void StrInvert (char *s)
{ 
    char tmp; 
    static int i=0;
    int len;
    len=strlen(s);

    if(i<len/2){
        tmp=s[i];
        s[i]=s[len-i-1];
        s[len-i-1] = tmp;
        i++;
        StrInvert (s);
        }
}

int main()
{
    char s[1000];
    gets(s);
    StrInvert(s);
    printf("%s\n", s);
    return 0;
}
