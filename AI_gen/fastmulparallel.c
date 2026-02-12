#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

void fillRandom(int **mat, int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = rand() % 10;
}

int **alloc2DArr(int r, int c)
{
    int **arr = malloc(r * sizeof(int *));
    for(int i = 0; i < r; i++)
        arr[i] = malloc(c * sizeof(int));
    return arr;
}

void free2DArr(int **arr, int r)
{
    for(int i = 0; i < r; i++)
        free(arr[i]);
    free(arr);
}

void multiplyRows(int **A, int **B, int n, int start, int rows)
{
    for(int i = start; i < start + rows; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int sum = 0;
            for(int k = 0; k < n; k++)
                sum += A[i][k] * B[k][j];
        }
    }
}

int main()
{
    srand(time(NULL));

    int sizes[3] = {500, 1000, 1500};
    int children[3] = {2, 4, 6};


    for(int s = 0; s < 3; s++)
    {
        int n = sizes[s];

        for(int c = 0; c < 3; c++)
        {
            int P = children[c];

            if(P > n)
                continue;

            int **mat1 = alloc2DArr(n, n);
            int **mat2 = alloc2DArr(n, n);

            fillRandom(mat1, n);
            fillRandom(mat2, n);

            int rows_per_child = n / P;
            int extra = n % P;
            int start_row = 0;

            struct timeval start, end;
            gettimeofday(&start, NULL);

            for(int i = 0; i < P; i++)
            {
                int rows = rows_per_child + (i < extra ? 1 : 0);

                pid_t pid = fork();

                if(pid == 0)   // Child
                {
                    multiplyRows(mat1, mat2, n, start_row, rows);
                    exit(0);
                }

                start_row += rows;
            }
            for(int i = 0; i < P; i++)
                wait(NULL);
                
            gettimeofday(&end, NULL);
            FILE*fp=fopen("time.txt","a");
            double time_taken =(end.tv_sec - start.tv_sec) * 1000.0 +(end.tv_usec - start.tv_usec) / 1000.0;
            fprintf(fp,"%d,%d,%lf\n", n, P, time_taken);
            fclose(fp);
            free2DArr(mat1, n);
            free2DArr(mat2, n);
        }
    }

    printf("\nAll results stored in time.txt\n");
    return 0;
}

