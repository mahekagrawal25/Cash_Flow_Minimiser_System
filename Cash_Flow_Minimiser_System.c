/*
DS Mini Project
Design an application using different data structures to provide a solution for any real-world problem

Topic: Cash Flow Minimizer System

Batch: I3
Group No: 2

Group Members:
 o UIT2023804 - Mahek Agrawal
 o UIT2023812 - Sejal Barapatre
 o UIT2023817 - Sneha Chavan
 o UIT2023852 - Manisha Patil
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_BANKS 100
#define MAX_TYPES 100

typedef struct Bank{
    char name[50];
    int netAmount;
    char types[MAX_TYPES][50];
    int typeCount;
} Bank;

int main(void) {
    // Declaration of functions
    int getMinIndex(Bank[], int);
    int getSimpleMaxIndex(Bank [], int);
    int findCommonType(Bank*, Bank*, char*);
    int getMaxIndex(Bank [], int , int , Bank[], int, char*);
    void printAns(int ansGraph[MAX_BANKS][MAX_BANKS], char paymentTypes[MAX_BANKS][MAX_BANKS][50], int, Bank []);
    void minimizeCashFlow(int, Bank[], int graph[MAX_BANKS][MAX_BANKS], int );
    
    printf("\n********************* Welcome to CASH FLOW MINIMIZER SYSTEM ***********************\n\n");
    printf("This system minimizes the number of transactions among multiple banks...\n");

    int numBanks;
    printf("Enter the number of banks participating in the transactions: ");
    scanf("%d", &numBanks);

    Bank input[MAX_BANKS];
    int graph[MAX_BANKS][MAX_BANKS] = {0};

    printf("\nPayment modes: GPay, PhonePe, Paytm, Amazon_Pay, PayPal\n\n");
    printf("Enter the details of the banks:\n");

    for (int i = 0; i < numBanks; i++) {
        printf("Bank %d name and number of payment modes:\n", i+1);
        scanf("%s", input[i].name);
        

        int numTypes;
        scanf("%d", &numTypes);
        input[i].typeCount = numTypes;
        
        printf("Enter the payment modes: ");
        for (int j = 0; j < numTypes; j++) {
            scanf("%s", input[i].types[j]);
        }
        printf("\n");
    }

    int numTransactions;
    printf("\n\nEnter the number of transactions: ");
    scanf("%d", &numTransactions);

    printf("\nEnter the details of transactions (debtor, creditor, amount):\n");
    for (int i = 0; i < numTransactions; i++) {
        char debtor[50], creditor[50];
        int amount;
        scanf("%s %s %d", debtor, creditor, &amount);

        int debtorIndex = -1, creditorIndex = -1;
        for (int j = 0; j < numBanks; j++) {
            if (strcmp(input[j].name, debtor) == 0) debtorIndex = j;
            if (strcmp(input[j].name, creditor) == 0) creditorIndex = j;
        }

        graph[debtorIndex][creditorIndex] = amount;
    }

    minimizeCashFlow(numBanks, input, graph, MAX_TYPES);
    
    printf("\nThank you for using Cash Flow Minimizer System !!\n");

    return 0;
}

// Function to get the index of the bank with the minimum net amount
int getMinIndex(Bank listOfNetAmounts[], int numBanks) {
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) continue;
        if (listOfNetAmounts[i].netAmount < min) {
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

// Function to get the index of the bank with the maximum net amount
int getSimpleMaxIndex(Bank listOfNetAmounts[], int numBanks) {
    int max = INT_MIN, maxIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) continue;
        if (listOfNetAmounts[i].netAmount > max) {
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

// Function to find a common payment type between two banks
int findCommonType(Bank *bank1, Bank *bank2, char *commonType) {
    for (int i = 0; i < bank1->typeCount; i++) {
        for (int j = 0; j < bank2->typeCount; j++) {
            if (strcmp(bank1->types[i], bank2->types[j]) == 0) {
                strcpy(commonType, bank1->types[i]);
                return 1;
            }
        }
    }
    return 0;
}

// Function to get the index of the bank with the maximum net amount that shares a payment type
int getMaxIndex(Bank listOfNetAmounts[], int numBanks, int minIndex, Bank input[], int maxNumTypes, char *matchingType) {
    int max = INT_MIN, maxIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount <= 0) continue;
        if (findCommonType(&listOfNetAmounts[minIndex], &listOfNetAmounts[i], matchingType)) {
            if (listOfNetAmounts[i].netAmount > max) {
                max = listOfNetAmounts[i].netAmount;
                maxIndex = i;
            }
        }
    }
    return maxIndex;
}

// Function to print the minimized cash flow transactions
void printAns(int ansGraph[MAX_BANKS][MAX_BANKS], char paymentTypes[MAX_BANKS][MAX_BANKS][50], int numBanks, Bank input[]) {
    printf("\nThe transactions for minimum cash flow are as follows:\n\n");
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (i != j && ansGraph[i][j] != 0) {
                printf("%s pays Rs %d to %s via %s\n", input[i].name, ansGraph[i][j], input[j].name, paymentTypes[i][j]);
                ansGraph[i][j] = 0;
            }
        }
    }
}

// Function to minimize the cash flow using the given graph
void minimizeCashFlow(int numBanks, Bank input[], int graph[MAX_BANKS][MAX_BANKS], int maxNumTypes) {
    Bank listOfNetAmounts[MAX_BANKS];
    int ansGraph[MAX_BANKS][MAX_BANKS] = {0};
    char paymentTypes[MAX_BANKS][MAX_BANKS][50] = {0};

    for (int b = 0; b < numBanks; b++) {
        strcpy(listOfNetAmounts[b].name, input[b].name);
        memcpy(listOfNetAmounts[b].types, input[b].types, sizeof(input[b].types));
        listOfNetAmounts[b].typeCount = input[b].typeCount;
        listOfNetAmounts[b].netAmount = 0;

        for (int i = 0; i < numBanks; i++) listOfNetAmounts[b].netAmount += graph[i][b];
        for (int j = 0; j < numBanks; j++) listOfNetAmounts[b].netAmount -= graph[b][j];
    }

    int numZeroNetAmounts = 0;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) numZeroNetAmounts++;
    }

    while (numZeroNetAmounts != numBanks) {
        int minIndex = getMinIndex(listOfNetAmounts, numBanks);
        char matchingType[50] = {0};
        int maxIndex = getMaxIndex(listOfNetAmounts, numBanks, minIndex, input, maxNumTypes, matchingType);

        //Matching Payment Mode not available
        if (maxIndex == -1) {
            int simpleMaxIndex = getSimpleMaxIndex(listOfNetAmounts, numBanks);
            int amount = abs(listOfNetAmounts[minIndex].netAmount);
            ansGraph[minIndex][0] += amount;
            strcpy(paymentTypes[minIndex][0], input[minIndex].types[0]);
            ansGraph[0][simpleMaxIndex] += amount;
            strcpy(paymentTypes[0][simpleMaxIndex], input[simpleMaxIndex].types[0]);

            listOfNetAmounts[simpleMaxIndex].netAmount += listOfNetAmounts[minIndex].netAmount;
            listOfNetAmounts[minIndex].netAmount = 0;
        } else {
            int transactionAmount = abs(listOfNetAmounts[minIndex].netAmount < listOfNetAmounts[maxIndex].netAmount ? listOfNetAmounts[minIndex].netAmount : listOfNetAmounts[maxIndex].netAmount);
            ansGraph[minIndex][maxIndex] += transactionAmount;
            strcpy(paymentTypes[minIndex][maxIndex], matchingType);

            listOfNetAmounts[minIndex].netAmount += transactionAmount;
            listOfNetAmounts[maxIndex].netAmount -= transactionAmount;
        }

        numZeroNetAmounts = 0;
        for (int i = 0; i < numBanks; i++) {
            if (listOfNetAmounts[i].netAmount == 0) numZeroNetAmounts++;
        }
    }

    printAns(ansGraph, paymentTypes, numBanks, input);
}


/*
OUTPUT:

********************* Welcome to CASH FLOW MINIMIZER SYSTEM ***********************

This system minimizes the number of transactions among multiple banks...
Enter the number of banks participating in the transactions: 6

Payment modes: GPay, PhonePe, Paytm, Amazon_Pay, PayPal

Enter the details of the banks:
Bank 1 name and number of payment modes:
SBI 1 Paytm
Bank 2 name and number of payment modes:
ICICI 3 GPay Paytm Amazon_Pay
Bank 3 name and number of payment modes:
HDFC 2 GPay Amazon_Pay
Bank 4 name and number of payment modes:
Wells_Fargo 1 Amazon_Pay
Bank 5 name and number of payment modes:
Axis 2 GPay Paytm
Bank 6 name and number of payment modes:
BOI 2 Amazon_Pay Paytm


Enter the number of transactions: 9

Enter the details of transactions (debtor, creditor, amount):
SBI ICICI 100
SBI HDFC 300
SBI Wells_Fargo 100
SBI Axis 100
ICICI HDFC 400
HDFC Wells_Fargo 200
Wells_Fargo Axis 500
BOI ICICI 300
BOI Wells_Fargo 100

The transactions for minimum cash flow are as follows:

SBI pays Rs 600 to Axis via Paytm
Wells_Fargo pays Rs 100 to HDFC via Amazon_Pay
BOI pays Rs 400 to HDFC via Amazon_Pay

Thank you for using Cash Flow Minimizer System !!

*/
