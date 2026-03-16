// Source: https://leetcode.com/problems/count-stepping-numbers-in-range/   |   Difficulty: Hard
//
// Problem Description:
// Given two positive integers low and high represented as strings, find the count of stepping numbers in the inclusive range [low, high].
//
// A stepping number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
//
// Return an integer denoting the count of stepping numbers in the inclusive range [low, high]. 
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note: A stepping number should not have a leading zero.
//
// Example:
// Input: low = "1", high = "11"
// Output: 10
// Explanation: The stepping numbers in the range [1,11] are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10. There are a total of 10 stepping numbers in the range. Hence, the output is 10.
//
// Constraints:
// 1 <= int(low) <= int(high) < 10100
// 	1 <= low.length, high.length <= 100
// 	low and high consist of only digits.
// 	low and high don't have any leading zeros.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countSteppingNumbers(char* low, char* high) {
    const int MOD = 1000000007;

    // Helper function to count stepping numbers up to a given limit
    int countUpTo(char* num) {
        int len = strlen(num);
        // DP array: dp[pos][last_digit][is_tight]
        int dp[101][10][2];
        memset(dp, 0, sizeof(dp));

        // Initialize for the first digit
        for (int d = 1; d <= num[0] - '0'; d++) {
            dp[0][d][d == (num[0] - '0')] = 1;
        }

        for (int pos = 1; pos < len; pos++) {
            for (int last = 0; last <= 9; last++) {
                for (int tight = 0; tight <= 1; tight++) {
                    int limit = tight ? (num[pos] - '0') : 9;
                    for (int d = 0; d <= limit; d++) {
                        if (abs(d - last) == 1) {
                            dp[pos][d][tight && (d == limit)] =
                                (dp[pos][d][tight && (d == limit)] + dp[pos - 1][last][tight]) % MOD;
                        }
                    }
                }
            }
        }

        // Sum up all valid stepping numbers of length len
        int total = 0;
        for (int last = 0; last <= 9; last++) {
            total = (total + dp[len - 1][last][1]) % MOD;
            total = (total + dp[len - 1][last][0]) % MOD;
        }
        return total;
    }

    // Count stepping numbers in range [low, high]
    int countHigh = countUpTo(high);
    int countLow = countUpTo(low);

    // Check if low itself is a stepping number
    bool isLowStepping = true;
    for (int i = 1; i < strlen(low); i++) {
        if (abs((low[i] - '0') - (low[i - 1] - '0')) != 1) {
            isLowStepping = false;
            break;
        }
    }

    int result = (countHigh - countLow + MOD) % MOD;
    if (isLowStepping) {
        result = (result + 1) % MOD;
    }
    return result;
}
