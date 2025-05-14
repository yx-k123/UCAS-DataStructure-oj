#include <stdio.h>

int main()
{
    char strA[100] = {0};
    char strB[100] = {0};
    int i = 0;
    char temp = 0;

    while(scanf("%c", &temp) != EOF)
    {
        if(temp == ',')
        {   
            continue;
        } else if(temp == '\n')
        {   
            strA[i] = '\0';
            break;
        } else
        {   
            strA[i] = temp;
            i++;
        }
    } 
    strA[i] = '\0';

    i = 0;
    while(scanf("%c", &temp) != EOF)
    {
        if(temp == ',')
        {   
            continue;
        } else if(temp == '\n')
        {   
            strB[i] = '\0';
            break;
        } else
        {   
            strB[i] = temp;
            i++;
        }
    } 
    strB[i] = '\0';

    if (strA[0] == 0 && strB[0] == 0)
    {
        printf("0\n");
        return 0;
    }

    int j = 0;
    while (strA[j] != 0 && strB[j] != 0)
    {   
        if (strA[j] == strB[j])
        {
            j++;
        } else {
            break;
        }
    }

    if (strA[j] == strB[j])
    {
        printf("0\n");
        return 0;
    } else if (strA[j] > strB[j])
    {
        printf("2\n");
        return 0;
    } else
    {
        printf("1\n");
        return 0;
    }
}