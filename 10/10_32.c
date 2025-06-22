#include <stdio.h>

int main()
{
    int a, b, c;
    a = 0;
    b = 0;
    c = 0;
    int temp;
    while (scanf("%d", &temp) != EOF)
    {
        switch (temp)
        {
        case 1:
            a++;
            break;
        case 2:
            b++;
            break;
        case 3:
            c++;
            break;

        default:
            break;
        }
    }

    while (a>0){
        printf("1 ", a--);
    }
    while (b>0){
        printf("2 ", b--);
    }
    while (c>0){
        printf("3 ", c--);
    }
    
    return 0;
}