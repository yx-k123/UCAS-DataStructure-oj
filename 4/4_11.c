#include <stdio.h>
#include <string.h>

int main()
{
    char str1[100];
    char str2[100];
    int a[100] = {0};
    char str3[100] = {0};

    for (int i = 0; i < 100; i++) {
        a[i] = -1;
    }

    scanf("%s", str1);
    scanf("%s", str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len3 = 0;

    for (int i = 0; i < len1; i++) {
        if (strchr(str2, str1[i]) == NULL && strchr(str3, str1[i]) == NULL) {
            a[len3] = i;
            str3[len3] = str1[i];
            len3++;
        }
    }

    
    if(len3 == 0) {
        printf("-1");
        return 0;
    }
    printf("%s ", str3);
    for (int i = 0; i < len3; i++) {
        if (a[i] != -1) {
            printf("%d", a[i]);
        }
    }
    return 0;
}
