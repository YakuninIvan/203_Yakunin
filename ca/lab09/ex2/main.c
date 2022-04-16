#include <stdio.h>

int main()
{
    int i, n;
    printf("Enter array size:\n");
    scanf("%d", &n);

    int* array = malloc(sizeof(int) * n);

    printf("Enter array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    int temp;

    for(int i = 0; i<n/2; i++){
        temp = array[i];
        array[i] = array[n-i-1];
        array[n-i-1] = temp;
    }

    printf("Array:\n");
    for (i = 0; i < n; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }

    free(array);

    return 0;
}
