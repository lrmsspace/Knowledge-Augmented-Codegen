// Source: https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/   |   Difficulty: Medium
//
// Problem Description:
// You have n bags numbered from 0 to n - 1. You are given two 0-indexed integer arrays capacity and rocks. The ith bag can hold a maximum of capacity[i] rocks and currently contains rocks[i] rocks. You are also given an integer additionalRocks, the number of additional rocks you can place in any of the bags.
//
// Return the maximum number of bags that could have full capacity after placing the additional rocks in some bags.
//
// Example:
// Input: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
// Output: 3
// Explanation:
// Place 1 rock in bag 0 and 1 rock in bag 1.
// The number of rocks in each bag are now [2,3,4,4].
// Bags 0, 1, and 2 have full capacity.
// There are 3 bags at full capacity, so we return 3.
// It can be shown that it is not possible to have more than 3 bags at full capacity.
// Note that there may be other ways of placing the rocks that result in an answer of 3.
//
// Constraints:
// n == capacity.length == rocks.length
// 	1 <= n <= 5 * 104
// 	1 <= capacity[i] <= 109
// 	0 <= rocks[i] <= capacity[i]
// 	1 <= additionalRocks <= 109
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

int maximumBags(int* capacity, int capacitySize, int* rocks, int rocksSize, int additionalRocks) {
    // Calculate the remaining capacity for each bag and store it in an array
    int* remainingCapacity = (int*)malloc(capacitySize * sizeof(int));
    for (int i = 0; i < capacitySize; i++) {
        remainingCapacity[i] = capacity[i] - rocks[i];
    }

    // Sort the remaining capacities in ascending order
    qsort(remainingCapacity, capacitySize, sizeof(int), compare);

    // Count how many bags can be filled with the additional rocks
    int count = 0;
    for (int i = 0; i < capacitySize; i++) {
        if (additionalRocks >= remainingCapacity[i]) {
            additionalRocks -= remainingCapacity[i];
            count++;
        } else {
            break;
        }
    }

    // Free the allocated memory for remaining capacities
    free(remainingCapacity);

    return count;       
}
