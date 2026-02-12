#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"myHeader.h"
#include <sys/wait.h>
#include<sys/mman.h>
#include <sys/time.h>
#include<time.h>

	
int main()
{       
	srand(time(NULL));
	srandom(time(NULL));
	int n;
	struct timeval start, end;
	int sizes[3]={500,1000,1500};
	int children[3]={2,4,6};
	for(int i=0;i<3;i++)
	{
		int n = sizes[i];
		for(int c = 0; c < 3; c++)
                {
                    int P = children[c];
                    if(P > n)continue;
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

		                if(pid == 0)
		                {
		                    mult2DArr(mat1,mat2,n,start_row,rows);
		                    exit(0);
		                }
		                start_row += rows;
                    }

               
				for(int j=0;j<children[c];j++)
				{
					wait(NULL);
				}
		
			gettimeofday(&end, NULL);
			double time_taken;
			time_taken = (end.tv_sec - start.tv_sec) * 1000.0;
			time_taken += (end.tv_usec - start.tv_usec) / 1000.0;
			FILE*fp=fopen("time.txt","a");
			fprintf(fp, "%d,%d,%lf\n",n,children[c],time_taken);
	    		fclose(fp);
	    	}
 	}
    	  printf("execution completed\n");
		
	return 0;
}

