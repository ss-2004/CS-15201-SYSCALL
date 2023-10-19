#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_DIM 10

int A[MAX_DIM][MAX_DIM];
int B[MAX_DIM][MAX_DIM];
int C[MAX_DIM][MAX_DIM];

int m, n, l;

struct Args {
    int row;
    int col;
};

void *multiply(void *arg) {
    struct Args *args = (struct Args *) arg;
    int row = args->row;
    int col = args->col;

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[row][i] * B[i][col];
    }
    C[row][col] = sum;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <m> <n> <l>\n", argv[0]);
        return 1;
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);
    l = atoi(argv[3]);

    if (m <= 0 || n <= 0 || l <= 0 || m > MAX_DIM || n > MAX_DIM || l > MAX_DIM) {
        printf("Invalid matrix dimensions. Dimensions must be positive integers less than or equal to %d\n", MAX_DIM);
        return 1;
    }

    printf("Enter matrix A (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter matrix B (%d x %d):\n", n, l);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    pthread_t threads[MAX_DIM][MAX_DIM];
    struct Args args[MAX_DIM][MAX_DIM];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < l; j++) {
            args[i][j].row = i;
            args[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, &args[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < l; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    printf("Resultant matrix C (%d x %d):\n", m, l);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < l; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
