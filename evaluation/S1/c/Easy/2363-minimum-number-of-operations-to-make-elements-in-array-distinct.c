// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. You need to ensure that the elements in the array are distinct. To achieve this, you can perform the following operation any number of times:
//
//
// 	Remove 3 elements from the beginning of the array. If the array has fewer than 3 elements, remove all remaining elements.
//
//
// Note that an empty array is considered to have distinct elements. Return the minimum number of operations needed to make the elements in the array distinct.
//
// Example:
// Input: nums = [1,2,3,4,2,3,3,5,7]
//
// Output: 2
//
// Explanation:
//
//
// 	In the first operation, the first 3 elements are removed, resulting in the array [4, 2, 3, 3, 5, 7].
// 	In the second operation, the next 3 elements are removed, resulting in the array [3, 5, 7], which has distinct elements.
//
//
// Therefore, the answer is 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-1d)
//   • When to use: Used for efficient string searching and pattern matching in linear time. It's also fundamental for various string algorithms that leverage self-matching properties.
//   • Idea: The prefix function computes for each position in a string the length of the longest proper prefix of its substring that is also a suffix of that substring. This forms the core of the Knuth-Morris-Pratt (KMP) algorithm, enabling linear time O(N) string matching.
//   • Invariants: For each i, pi[i] is the length of the longest proper prefix of s[0...i] that is also a suffix of s[0...i].; The current j (length of the matched prefix) always represents pi[i-1] or a shorter valid prefix length.
//   • Tips: The prefix function array (pi array) stores lengths, not indices.; It can be used to build the KMP automaton for pattern matching.
//   • Pitfalls: Confusing proper prefix/suffix with non-proper ones.; Incorrectly handling the base case pi[0] = 0.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumOperations(int* nums, int numsSize) {
    int freq[101] = {0};
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i]]++;
    }

    int duplicates = 0;
    for (int i = 1; i <= 100; ++i) {
        if (freq[i] > 1) {
            duplicates += freq[i] - 1;
        }
    }

    return (duplicates + 2) / 3;        
}
