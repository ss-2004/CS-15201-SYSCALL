/*
 * Q1a : 
 * Write a program to simulate deposit/withdraw activities on a banking account: 
 * Initialize the beginning balance (global variable) to 1 million, withdraw 600 thousands, and then deposit 500 thousands. 
 * Create two Posix threads in main(), which call the withdraw and the deposit functions respectively. 
 * Both withdraw and deposit functions have one parameter, which represent the amount to withdraw or deposit. 
 * You can create these two threads in any order to perform withdraw and deposit action. 
 * However, before you create the second thread, use pthread_join() to wait for the first thread to terminate. 
 * Finally print out the ending balance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double balance = 1000000.0;
pthread_mutex_t balance_mutex = PTHREAD_MUTEX_INITIALIZER;

void *withdraw(void *arg) {
    double amount = *(double *) arg;
    pthread_mutex_lock(&balance_mutex);
    if (amount <= balance) {
        balance -= amount;
        printf("Withdrawn $%.2f\n", amount);
    } else {
        printf("Insufficient balance for withdrawal: $%.2f\n", amount);
    }
    pthread_mutex_unlock(&balance_mutex);
    pthread_exit(NULL);
}

void *deposit(void *arg) {
    double amount = *(double *) arg;
    pthread_mutex_lock(&balance_mutex);
    balance += amount;
    printf("Deposited $%.2f\n", amount);
    pthread_mutex_unlock(&balance_mutex);
    pthread_exit(NULL);
}

int main() {
    double withdraw_amount = 600000.0;
    double deposit_amount = 500000.0;
    pthread_t withdraw_thread, deposit_thread;

    if (pthread_create(&withdraw_thread, NULL, withdraw, &withdraw_amount) != 0) {
        perror("Error creating withdraw thread");
        return 1;
    }

    pthread_join(withdraw_thread, NULL);
    if (pthread_create(&deposit_thread, NULL, deposit, &deposit_amount) != 0) {
        perror("Error creating deposit thread");
        return 1;
    }

    pthread_join(deposit_thread, NULL);
    printf("Ending balance: $%.2f\n", balance);
    return 0;
}

