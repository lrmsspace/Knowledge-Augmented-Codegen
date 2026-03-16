// Source: https://leetcode.com/problems/rearranging-fruits/   |   Difficulty: Hard
//
// Problem Description:
// You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
//
//
// 	Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
// 	The cost of the swap is min(basket1[i], basket2[j]).
//
//
// Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.
//
// Return the minimum cost to make both the baskets equal or -1 if impossible.
//
// Example:
// Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
// Output: 1
// Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.
//
// Constraints:
// basket1.length == basket2.length
// 	1 <= basket1.length <= 105
// 	1 <= basket1[i], basket2[i] <= 109
//

long long minCost(int* basket1, int basket1Size, int* basket2, int basket2Size) {
    if (basket1Size != basket2Size) return -1;
    int n = basket1Size;

    /* count frequencies */
    #define MAX_VAL 1000000000
    #define MIN_VAL 1
    #define RANGE (MAX_VAL - MIN_VAL + 1)
    int *freq = (int*)calloc(RANGE, sizeof(int));
    if (!freq) return -1;

    int globalMin = MAX_VAL + 1;
    for (int i = 0; i < n; ++i) {
        freq[basket1[i] - MIN_VAL]++;
        freq[basket2[i] - MIN_VAL]--;
        if (basket1[i] < globalMin) globalMin = basket1[i];
        if (basket2[i] < globalMin) globalMin = basket2[i];
    }

    /* check feasibility and collect surplus elements */
    int surplusCount = 0;
    for (int i = 0; i < RANGE; ++i) {
        if (freq[i] % 2 != 0) {
            free(freq);
            return -1; /* impossible to balance */
        }
        if (freq[i] > 0) surplusCount += freq[i] / 2;
    }

    int *surplus = (int*)malloc(surplusCount * sizeof(int));
    if (!surplus) {
        free(freq);
        return -1;
    }
    int idx = 0;
    for (int i = 0; i < RANGE; ++i) {
        while (freq[i] > 0) {
            surplus[idx++] = i + MIN_VAL;
            freq[i] -= 2;
        }
    }
    free(freq);

    /* calculate minimum cost */
    long long totalCost = 0;
    for (int i = 0; i < surplusCount; ++i) {
        int directSwapCost = surplus[i];
        int doubleGlobalMinCost = 2 * globalMin;
        totalCost += (directSwapCost < doubleGlobalMinCost) ? directSwapCost : doubleGlobalMinCost;
    }

    free(surplus);
    return totalCost;       
}
