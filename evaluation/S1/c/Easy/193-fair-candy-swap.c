// Source: https://leetcode.com/problems/fair-candy-swap/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob have a different total number of candies. You are given two integer arrays aliceSizes and bobSizes where aliceSizes[i] is the number of candies of the ith box of candy that Alice has and bobSizes[j] is the number of candies of the jth box of candy that Bob has.
//
// Since they are friends, they would like to exchange one candy box each so that after the exchange, they both have the same total amount of candy. The total amount of candy a person has is the sum of the number of candies in each box they have.
//
// Return an integer array answer where answer[0] is the number of candies in the box that Alice must exchange, and answer[1] is the number of candies in the box that Bob must exchange. If there are multiple answers, you may return any one of them. It is guaranteed that at least one answer exists.
//
// Example:
// Input: aliceSizes = [1,1], bobSizes = [2,2]
// Output: [1,2]
//
// Constraints:
// 1 <= aliceSizes.length, bobSizes.length <= 104
// 	1 <= aliceSizes[i], bobSizes[j] <= 105
// 	Alice and Bob have a different total number of candies.
// 	There will be at least one valid answer for the given input.
//
// Helpful references (internal KB):
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* fairCandySwap(int* aliceSizes, int aliceSizesSize, int* bobSizes, int bobSizesSize, int* returnSize) {
    int sumA = 0, sumB = 0;
    for (int i = 0; i < aliceSizesSize; i++) {
        sumA += aliceSizes[i];
    }
    for (int j = 0; j < bobSizesSize; j++) {
        sumB += bobSizes[j];
    }

    int delta = (sumB - sumA) / 2;

    // Use a hash table to store Bob's candy sizes for O(1) lookups
    int maxCandySize = 100000; // Given constraint: 1 <= aliceSizes[i], bobSizes[j] <= 10^5
    char *bobCandyMap = (char *)calloc(maxCandySize + 1, sizeof(char));
    for (int j = 0; j < bobSizesSize; j++) {
        bobCandyMap[bobSizes[j]] = 1;
    }

    int *result = (int *)malloc(2 * sizeof(int));
    for (int i = 0; i < aliceSizesSize; i++) {
        int targetBobCandy = aliceSizes[i] + delta;
        if (targetBobCandy >= 1 && targetBobCandy <= maxCandySize && bobCandyMap[targetBobCandy]) {
            result[0] = aliceSizes[i];
            result[1] = targetBobCandy;
            *returnSize = 2;
            free(bobCandyMap);
            return result;
        }
    }

    // Cleanup in case no solution is found (though the problem guarantees one)
    free(bobCandyMap);
    free(result);
    *returnSize = 0;
    return NULL;        
}
