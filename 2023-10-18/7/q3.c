#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_DIM 100

struct thrdArgs{
    int r;
    int c;
    int n;
    int **matA;
    int **matB;
    int **rslt; 
};

void *mul(void *arg){
    int sum=0;
    struct thrdArgs *args = (struct thrdArgs *)arg;

    for(int i=0; i<args->n; i++){
        sum += args->matA[args->r][i] * args->matB[i][args->c];
    } 

    args->rslt[args->r][args->c] = sum;
    pthread_exit(NULL);
}

int main(int argc, char** argv){
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int l = atoi(argv[3]);

    if(m<=0 || n <=0 || l<=0 || m > MAX_DIM || n > MAX_DIM || l > MAX_DIM){
        printf("INVALID DIMENSIONS!\n");
        return 1;
    }

    int matA[MAX_DIM][MAX_DIM];
    int matB[MAX_DIM][MAX_DIM];
    int rslt[MAX_DIM][MAX_DIM];

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++)
            matA[i][j]=i*n+j;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<l; j++)
            matB[i][j]=i*l+j;
    }

    pthread_t thrds[MAX_DIM][MAX_DIM];
    struct thrdArgs ta[MAX_DIM][MAX_DIM];

    for(int i=0; i<m; i++){
        for(int j=0; j<l; j++){
            ta[i][j].r = i;
            ta[i][j].c = j;
            ta[i][j].n = n;
            ta[i][j].matA = matA;
            ta[i][j].matB = matB;
            ta[i][j].rslt = rslt;

            if(pthread_create(&thrds[i][j], NULL, mul, &ta[i][j]) != 0){
                perror("Thread creation failed!\n");
                return 1;
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<l; j++)
            pthread_join(thrds[i][j], NULL);
    }

    printf("Result matrix : \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<l; j++)
            printf("%d\t", rslt[i][j]);
        printf("\n");
    }
    return 0;
}