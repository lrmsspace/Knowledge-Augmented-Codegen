// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given 3 positive integers zero, one, and limit.
//
// A binary array arr is called stable if:
//
//
// 	The number of occurrences of 0 in arr is exactly zero.
// 	The number of occurrences of 1 in arr is exactly one.
// 	Each subarray of arr with a size greater than limit must contain both 0 and 1.
//
//
// Return the total number of stable binary arrays.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: zero = 1, one = 1, limit = 2
//
// Output: 2
//
// Explanation:
//
// The two possible stable binary arrays are [1,0] and [0,1], as both arrays have a single 0 and a single 1, and no subarray has a length greater than 2.
//
// Constraints:
// 1 <= zero, one, limit <= 200
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfStableArrays(int zero, int one, int limit) {
    const int MOD = 1000000007;
    int dp[201][201][2] = {0};
    dp[0][0][0] = 1; // Base case: empty array

    for (int z = 0; z <= zero; z++) {
        for (int o = 0; o <= one; o++) {
            for (int last = 0; last <= 1; last++) {
                if (dp[z][o][last] == 0) continue;

                // Add a 0
                if (z < zero) {
                    int canAddZero = 1;
                    if (last == 0) {
                        // Check limit constraint
                        for (int k = 1; k < limit && z + k <= zero; k++) {
                            if (dp[z + k][o][0] > 0) {
                                canAddZero = 0;
                                break;
                            }
                        }
                    }
                    if (canAddZero) {
                        dp[z + 1][o][0] = (dp[z + 1][o][0] + dp[z][o][last]) % MOD;
                    }
                }

                // Add a 1
                if (o < one) {
                    int canAddOne = 1;
                    if (last == 1) {
                        // Check limit constraint
                        for (int k = 1; k < limit && o + k <= one; k++) {
                            if (dp[z][o + k][1] > 0) {
                                canAddOne = 0;
                                break;
                            }
                        }
                    }
                    if (canAddOne) {
                        dp[z][o + 1][1] = (dp[z][o + 1][1] + dp[z][o][last]) % MOD;
                    }
                }
            }
        }
    }

    return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
}
