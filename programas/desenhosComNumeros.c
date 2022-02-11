#include <stdio.h>

void quadrado(int high)
{
    int i, j;
    for (int i = 1; i < high + 1; i++)
    {
        printf("%d ", i);
        if (i == 1)
        {
            for (j = i + 1; j < high; j++)
                printf("%d ", j);
        }
        else if (i == high)
        {
            for (j = i - 1; j > 1; j--)
                printf("%d ", j);
        }else{
            for (j = 0; j < high + 1; j++)
                printf(" ");
        }
        printf("%d\n", high - i + 1);
    }
}

void piramide(int high)
{
    for (int i = high; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
            printf(" ");
        for (int k = 0; k <= high - i; k++)
            printf("%d ", i);
        printf("\n");
    }
}

int main()
{
    //piramide(5);
    quadrado(5);
    return 0;
}