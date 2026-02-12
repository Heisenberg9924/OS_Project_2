#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"myHeader2.h"
#include<sys/time.h>
#include<time.h>

void fillRandom(int **mat, int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j]=random()%10;
}

int main()
{
    srandom(time(NULL));

    int sizes[3]={500,1000,1500};
    struct timeval start,end;

    FILE *fp=fopen("timeseq.txt","w");
    fprintf(fp,"MatrixSize,Time(ms)\n");

    for(int s=0;s<3;s++)
    {
        int n=sizes[s];

        int **mat1=alloc2DArr(n,n);
        int **mat2=alloc2DArr(n,n);

        fillRandom(mat1,n);
        fillRandom(mat2,n);

        gettimeofday(&start,NULL);

        int **ans = mult2DArr(mat1,n,n,mat2,n,n);

        gettimeofday(&end,NULL);

        double time_taken=
            (end.tv_sec-start.tv_sec)*1000.0+
            (end.tv_usec-start.tv_usec)/1000.0;

        fprintf(fp,"%d,%lf\n",n,time_taken);

  
    }

    fclose(fp);

    return 0;
}

