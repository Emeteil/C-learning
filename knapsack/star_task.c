#include <stdio.h>

void swap(unsigned int* a, unsigned int* b)  
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(unsigned int* array, unsigned int size)  
{
    int i, j;
    for (i = 0; i < size - 1; ++i) {
        for (j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);
        }
    }
}

unsigned int max(unsigned int a, unsigned int b) {
    if (a >= b) return a;
    return b;
}

unsigned int knapsack(unsigned int W, unsigned int* weights, unsigned int n) {
    unsigned int dp[n + 1][W + 1];

    // dp[i][j] stores the maximum weight that can be gained using the first i ingots and a backpack of capacity j

    for (int i = 0; i < (n + 1); i++)
        for (int j = 0; j < (W + 1); j++)
            dp[i][j] = 0;

    for (int i = 1; i < (n + 1); i++) {
        for (int j = 0; j < (W + 1); j++) {
            // iterate over all ingots (i from 1 to n) and over all possible backpack capacities (j from 0 to W)
            if (weights[i - 1] > j)
                dp[i][j] = dp[i - 1][j]; // предыдущий
                // If the weight of the ingot weights[i-1] is greater than the current capacity of the backpack j, we don't take this ingot.
                // In this case dp[i][j] will be equal to dp[i-1][j] -> maximum weight that can be gained without taking the current ingot into account
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + weights[i - 1]);// для предыдущей вместимости или весь прошлый вес+новый
                // dp[i-1][j] - maximum weight that can be gained without taking into account the current ingot
                // dp[i-1][j-weights[i-1]] + weights[i-1] - maximum weight that can be gained by taking the current ingot and adding its weight to the maximum weight that can be gained without it.
        }
    }

    // n -> all weights
    // W -> total capacity
    return dp[n][W];
}

int main() {
    FILE *file = fopen("input_1.txt", "r");

    if (file == NULL) return 1;

    unsigned int W = 0;
    unsigned int n = 0;

    fscanf(file, "%u %u\n", &W, &n);

    unsigned int gold_ingot[n];

    for (int i = 0; i < n; i++) {
        fscanf(file, "%u", &gold_ingot[i]);
    }

    // optionally
    bubble_sort(gold_ingot, n);

    unsigned int max_occupancy = knapsack(W, gold_ingot, n);

    printf("Максимально можно унести %u килограмм!\n", max_occupancy);

    return 0;
}