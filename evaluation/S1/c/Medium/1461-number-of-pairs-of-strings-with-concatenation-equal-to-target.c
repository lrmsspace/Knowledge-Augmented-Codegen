// Source: https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of digit strings nums and a digit string target, return the number of pairs of indices (i, j) (where i != j) such that the concatenation of nums[i] + nums[j] equals target.
//
// Example:
// Input: nums = ["777","7","77","77"], target = "7777"
// Output: 4
// Explanation: Valid pairs are:
// - (0, 1): "777" + "7"
// - (1, 0): "7" + "777"
// - (2, 3): "77" + "77"
// - (3, 2): "77" + "77"
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i].length <= 100
// 	2 <= target.length <= 100
// 	nums[i] and target consist of digits.
// 	nums[i] and target do not have leading zeros.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
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

int numOfPairs(char** nums, int numsSize, char* target) {
    int count = 0;
    int targetLen = 0;
    while (target[targetLen] != '\0') {
        targetLen++;
    }

    for (int i = 0; i < numsSize; i++) {
        int len1 = 0;
        while (nums[i][len1] != '\0') {
            len1++;
        }

        for (int j = 0; j < numsSize; j++) {
            if (i == j) {
                continue;
            }

            int len2 = 0;
            while (nums[j][len2] != '\0') {
                len2++;
            }

            if (len1 + len2 != targetLen) {
                continue;
            }

            int k;
            for (k = 0; k < len1; k++) {
                if (nums[i][k] != target[k]) {
                    break;
                }
            }
            if (k != len1) {
                continue;
            }

            for (k = 0; k < len2; k++) {
                if (nums[j][k] != target[len1 + k]) {
                    break;
                }
            }
            if (k == len2) {
                count++;
            }
        }
    }

    return count;       
}
