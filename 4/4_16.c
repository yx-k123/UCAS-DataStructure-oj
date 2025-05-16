#include <stdio.h>
#include <string.h>

int StrCompare(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for (int i = 0; i < len1 && i < len2; i++)
    {
        if (str1[i] > str2[i])
        {
            return 1;
        }
        else if (str1[i] < str2[i])
        {
            return -1;
        }
        else
        {
            continue;
        }
    }
    if (len1 > len2)
    {
        return 1;
    }
    else if (len1 < len2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char str1[100] = {0};
    char str2[100] = {0};
    scanf("%s", str1);
    scanf("%s", str2);
    int n = StrCompare(str1, str2);
    printf("%d\n", n);
    return 0;
}