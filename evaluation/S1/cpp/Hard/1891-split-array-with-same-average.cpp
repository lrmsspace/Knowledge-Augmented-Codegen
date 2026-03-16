// Source: https://leetcode.com/problems/split-array-with-same-average/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// You should move each element of nums into one of the two arrays A and B such that A and B are non-empty, and average(A) == average(B).
//
// Return true if it is possible to achieve that and false otherwise.
//
// Note that for an array arr, average(arr) is the sum of all the elements of arr over the length of arr.
//
// Example:
// Input: nums = [1,2,3,4,5,6,7,8]
// Output: true
// Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have an average of 4.5.
//
// Constraints:
// 1 <= nums.length <= 30
// 	0 <= nums[i] <= 104
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size();
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        // dp[i][j] indicates whether a sum of j can be formed with i elements
        vector<vector<bool>> dp(n + 1, vector<bool>(totalSum + 1, false));
        dp[0][0] = true;

        for (int num : nums) {
            for (int i = n - 1; i >= 0; --i) {
                for (int j = totalSum - num; j >= 0; --j) {
                    if (dp[i][j]) {
                        dp[i + 1][j + num] = true;
                    }
                }
            }
        }

        for (int lenA = 1; lenA <= n / 2; ++lenA) {
            if ((totalSum * lenA) % n == 0) {
                int targetSumA = (totalSum * lenA) / n;
                if (dp[lenA][targetSumA]) {
                    return true;
                }
            }
        }

        return false;           
    }
};
