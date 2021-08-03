/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 

// SungChanChoi 201824641
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    //int s = 5; sets 64
    //int E = 1; line 1.
    //int b = 5; 32bit
    
	int blk;
    int row, col, i, j;
    int k, l, m, n, o, p, q;
    if (M == 32) 
    {
        blk = 8;
        for (row = 0; row < N; row += blk)
        {
            for (col = 0; col < M; col += blk)
            {
                for (i = row; i < row + blk && i < N; ++i)
                {
                    for (j = col; j < col + blk && j < M; ++j)
                    {
                        if (i != j) 
                        {
                            B[j][i] = A[i][j];
                        } 
                    }
                    if (row == col) 
                    {
                        B[i][i] = A[i][i];
                    }
                }
            }
        }
    }

    if (M == 64)
    {
        blk = 8;
        for (row = 0; row < N; row += blk)
        {
            for (col = 0; col < M; col += blk)
            {
				for(i = 0; i < blk ; ++i)
                {
					j = A[row + i][col];
					k = A[row + i][col + 1];
					l = A[row + i][col + 2];
					m = A[row + i][col + 3];

                    B[col][row + i] = j;
                    B[col + 1][row + i] = k;
                    B[col + 2][row + i] = l;
                    B[col + 3][row + i] = m;
				}
				for(i = 0; i < blk; ++i)
                {
					n = A[row + i][col + 4];
					o = A[row + i][col + 5];
					p = A[row + i][col + 6];
					q = A[row + i][col + 7];

                    B[col + 4][row + i] = n;
                    B[col + 5][row + i] = o;
                    B[col + 6][row + i] = p;
                    B[col + 7][row + i] = q;
				}
            }
        }
    }

    if (M == 61 && N == 67) 
    {
        blk = 18;
        for (row = 0; row < N; row += blk)
        {
            for (col = 0; col < M; col += blk)
            {
                for (i = row; i < row + blk && i < N; ++i)
                {
                    for (j = col; j < col + blk && j < M; ++j)
                    {
                        B[j][i] = A[i][j];
                    }
                }
            }
        }
    }
}


/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

