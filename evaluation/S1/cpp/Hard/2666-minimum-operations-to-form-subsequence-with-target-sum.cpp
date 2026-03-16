// Source: https://leetcode.com/problems/minimum-operations-to-form-subsequence-with-target-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums consisting of non-negative powers of 2, and an integer target.
//
// In one operation, you must apply the following changes to the array:
//
//
// 	Choose any element of the array nums[i] such that nums[i] > 1.
// 	Remove nums[i] from the array.
// 	Add two occurrences of nums[i] / 2 to the end of nums.
//
//
// Return the minimum number of operations you need to perform so that nums contains a subsequence whose elements sum to target. If it is impossible to obtain such a subsequence, return -1.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [1,2,8], target = 7
// Output: 1
// Explanation: In the first operation, we choose element nums[2]. The array becomes equal to nums = [1,2,4,4].
// At this stage, nums contains the subsequence [1,2,4] which sums up to 7.
// It can be shown that there is no shorter sequence of operations that results in a subsequnce that sums up to 7.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 230
// 	nums consists only of non-negative powers of two.
// 	1 <= target < 231
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
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(vector<int>& nums, int target) {
        int count[31] = {0};
        for (int num : nums) {
            int power = 0;
            while ((1 << power) < num) {
                power++;
            }
            count[power]++;
        }

        int operations = 0;
        for (int i = 0; i < 31; ++i) {
            if (target & (1 << i)) {
                if (count[i] > 0) {
                    count[i]--;
                } else {
                    int j = i + 1;
                    while (j < 31 && count[j] == 0) {
                        j++;
                    }
                    if (j == 31) {
                        return -1;
                    }
                    while (j > i) {
                        count[j]--;
                        count[j - 1] += 2;
                        operations++;
                        j--;
                    }
                    count[i]--;
                }
            }
            if (i < 30) {
                count[i + 1] += count[i] / 2;
            }
        }

        return operations;          
    }
};
