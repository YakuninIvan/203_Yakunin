#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    swap(&x, &y);
    printf("%d\n", x);
    printf("%d", y);
    return 0;
}
