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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minCost(int* basket1, int basket1Size, int* basket2, int basket2Size) {
    // Step 1: Calculate the frequency of each fruit cost in both baskets
    // and find the minimum cost of any fruit across both baskets.
    long long totalCost = 0;
    int minCost = INT_MAX;
    int freq[100001] = {0}; // Frequency array for costs up to 100000

    for (int i = 0; i < basket1Size; i++) {
        freq[basket1[i]]++;
        if (basket1[i] < minCost) {
            minCost = basket1[i];
        }
    }

    for (int i = 0; i < basket2Size; i++) {
        freq[basket2[i]]--;
        if (basket2[i] < minCost) {
            minCost = basket2[i];
        }
    }

    // Step 2: Check if it's possible to make the baskets equal
    for (int i = 0; i <= 100000; i++) {
        if (freq[i] % 2 != 0) {
            return -1; // Impossible to make baskets equal
        }
    }

    // Step 3: Calculate the minimum cost to make the baskets equal
    for (int i = 0; i <= 100000; i++) {
        while (freq[i] > 0) {
            totalCost += (long long)min(i, minCost);
            freq[i] -= 2; // We can swap two fruits at a time
        }
    }

    return totalCost;       
}
