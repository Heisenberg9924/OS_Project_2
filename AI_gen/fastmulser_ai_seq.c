#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

/* Function to allocate a 2D array dynamically */
int **createMatrix(int rows, int cols)
{
    int **mat = (int **)malloc(rows * sizeof(int *));
    if (mat == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        mat[i] = (int *)malloc(cols * sizeof(int));
        if (mat[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    return mat;
}

/* Function to free allocated 2D array */
void freeMatrix(int **mat, int rows)
{
    for (int i = 0; i < rows; i++)
        free(mat[i]);
    free(mat);
}

/* Fill matrix with random numbers (0–9) */
void fillRandom(int **mat, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10;
}

/* Matrix multiplication */
int **multiplyMatrix(int **A, int r1, int c1, int **B, int r2, int c2)
{
    if (c1 != r2) {
        printf("Matrix multiplication not possible\n");
        return NULL;
    }

    int **result = createMatrix(r1, c2);

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

int main()
{
    srand(time(NULL));

    int sizes[3] = {500, 1000, 1500};
    struct timeval start, end;

    FILE *fp = fopen("timeseq.txt", "w");
    if (fp == NULL) {
        printf("File opening failed\n");
        return 1;
    }

    fprintf(fp, "MatrixSize,Time(ms)\n");

    for (int s = 0; s < 3; s++)
    {
        int n = sizes[s];

        int **mat1 = createMatrix(n, n);
        int **mat2 = createMatrix(n, n);

        fillRandom(mat1, n);
        fillRandom(mat2, n);

        gettimeofday(&start, NULL);

        int **ans = multiplyMatrix(mat1, n, n, mat2, n, n);

        gettimeofday(&end, NULL);

        double time_taken =
            (end.tv_sec - start.tv_sec) * 1000.0 +
            (end.tv_usec - start.tv_usec) / 1000.0;

        fprintf(fp, "%d,%lf\n", n, time_taken);

        /* Free allocated memory */
        freeMatrix(mat1, n);
        freeMatrix(mat2, n);
        freeMatrix(ans, n);
    }

    fclose(fp);

    return 0;
}
