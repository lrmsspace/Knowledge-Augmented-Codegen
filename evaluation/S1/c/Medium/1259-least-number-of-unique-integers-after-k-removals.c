// Source: https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
//
// Example:
// Input: arr = [5,5,4], k = 1
// Output: 1
// Explanation: Remove the single 4, only 5 is left.
//
// Constraints:
// 1 <= arr.length <= 10^5
// 	1 <= arr[i] <= 10^9
// 	0 <= k <= arr.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findLeastNumOfUniqueInts(int* arr, int arrSize, int k){


    int freq[100001] = {0};
    for (int i = 0; i < arrSize; i++) {
        freq[arr[i]]++;
    }

    int countFreq[100001] = {0};
    for (int i = 0; i < 100001; i++) {
        if (freq[i] > 0) {
            countFreq[freq[i]]++;
        }
    }

    int uniqueCount = 0;
    for (int i = 1; i <= 100000; i++) {
        if (countFreq[i] > 0) {
            int canRemove = countFreq[i] * i;
            if (k >= canRemove) {
                k -= canRemove;
                uniqueCount += countFreq[i];
            } else {
                uniqueCount += k / i;
                k = 0;
                break;
            }
        }
    }

    for (int i = 1; i <= 100000 && k > 0; i++) {
        if (countFreq[i] > 0) {
            int canRemove = countFreq[i] * i;
            if (k >= canRemove) {
                k -= canRemove;
                uniqueCount += countFreq[i];
            } else {
                uniqueCount += k / i;
                k = 0;
                break;
            }
        }
    }

    int totalUnique = 0;
    for (int i = 1; i <= 100000; i++) {
        if (countFreq[i] > 0) {
            totalUnique += countFreq[i];
        }
    }

    return totalUnique - uniqueCount;
}
