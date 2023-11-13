/*
 * Write a program that simulates a game of Nim. The program should allow the user to enter the number of players (N) and the initial token value (tokVal). The program should then create N pipes for communication between the players. Each pipe should be bidirectional.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAX_PLAYERS 10

int N, tokVal, P;
int points[MAX_PLAYERS];
int pipes[MAX_PLAYERS][2];

void handler(int signum) {
    printf("\n\tI am player number %d. \n\tI have been killed.\n", getpid());
    exit(0);
}

void play_game(int player_number) {
    int token;
    int next_player = (player_number + 1) % N;

    while (1) {
        read(pipes[player_number][0], &token, sizeof(token));

        printf("\n\tI am player number %d.\n\tI have received a token with value %d\n\tI am now sending token to player %d.\n\tMy current points are %d.\n",
               player_number, token, next_player, points[player_number]);

        if (token == 0) {
            points[player_number]++;
            if (points[player_number] == P) {
                printf("\n\tI am player number %d.\n\tI have %d points.\n\tI have won!!!\n", player_number,
                       points[player_number]);

                for (int i = 0; i < N; ++i) {
                    if (i != player_number) {
                        kill(getpid() + i, SIGTERM);
                    }
                }
                exit(0);
            }
            token = tokVal;
        } else {
            token--;
        }

        write(pipes[next_player][1], &token, sizeof(token));
    }
}

int main() {
    printf("Enter the number of players (N): ");
    scanf("%d", &N);

    printf("Enter the initial token value (tokVal): ");
    scanf("%d", &tokVal);

    printf("Enter the points required to win (P): ");
    scanf("%d", &P);

    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            pipe(pipes[i]);
            pipe(pipes[N - 1]);
        } else {
            pipe(pipes[i]);
        }
    }

    for (int i = 0; i < N; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
            signal(SIGTERM, handler);
            play_game(i);
        }
    }

    int initial_token = tokVal;
    write(pipes[0][1], &initial_token, sizeof(initial_token));

    for (int i = 0; i < N; ++i) {
        wait(NULL);
    }

    return 0;
}
