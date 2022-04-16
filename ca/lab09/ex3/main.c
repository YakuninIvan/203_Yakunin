#include <stdio.h>

int main()
{
    int i, n, m;
    printf("Insert number"
           " of rows and columns:\n");
    scanf("%d %d", &n, &m);
    int** matrix1 = malloc(sizeof(int) * n * m);
    int** matrix2 = malloc(sizeof(int) * n * m);

    for(int i = 0; i < n; i++)
    {
        matrix1[i] = malloc(m * sizeof(int));
    }

    for(int i = 0; i < m; i++)
    {
        matrix2[i] = malloc(n * sizeof(int));
    }

    printf("Enter matrix:\n");
    for (i = 0; i < n; i++)
    {
        printf("Enter row %d:\n", i + 1);
        for(int t = 0; t < m; t++)
        {
            scanf("%d", &matrix1[i][t]);
        }
    }

    for (i = 0; i < n; i++)
    {
        for(int t = 0; t < m; t++)
        {
            matrix2[t][i] = matrix1[i][t];
        }
    }

    printf("Matrix:\n");
    for (i = 0; i < m; i++)
    {
        for(int t = 0; t < n; t++)
        {
            printf("%d ", matrix2[i][t]);
        }
        printf("\n");
    }

    for(int i = 0; i < n; i++)
    {
        free(matrix1[i]);
    }
    for(int i = 0; i < m; i++)
    {
        free(matrix2[i]);
    }

    free(matrix1);
    free(matrix2);

    return 0;
}
