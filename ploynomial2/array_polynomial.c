#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[128] = {0 ,};
    int arr2[128] = {0 ,};

    arr[1] = 5;
    arr[2] = 2;
    arr[5] = -3;

    arr2[1] = 23;
    arr2[3] = 4;
    arr2[5] = 3;
    for(int i = 127; i; i--)
    {
        if (arr[i] || arr2[i])
        {
        if (arr[i] && arr2[i])
        {
            printf("%dx ^ %d",arr[i] + arr2[i], i);
        }
        else if (arr[i])
        {
            printf("%dx ^ %d",arr[i], i);
        }
        else if (arr2[i])
        {
            printf("%dx ^ %d",arr2[i], i);
        }
        if (i > 1)
        {
            printf(" + ");
        }
        }
        else
        {
            ;
        }
    }
    return 0;
}