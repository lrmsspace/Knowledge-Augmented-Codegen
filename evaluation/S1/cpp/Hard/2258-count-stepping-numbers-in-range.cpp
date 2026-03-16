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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countSteppingNumbers(string low, string high) {
        const int MOD = 1e9 + 7;

        auto dpCount = [&](const string& num) {
            int n = num.size();
            vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(10, 0)));

            // Base case: single-digit stepping numbers
            for (int d = 1; d <= num[0] - '0'; ++d) {
                dp[1][d == (num[0] - '0')][d] = 1;
            }

            for (int i = 1; i < n; ++i) {
                for (int tight = 0; tight <= 1; ++tight) {
                    int limit = tight ? (num[i] - '0') : 9;
                    for (int lastDigit = 0; lastDigit <= 9; ++lastDigit) {
                        if (dp[i][tight][lastDigit] == 0) continue;
                        for (int d = 0; d <= limit; ++d) {
                            if (abs(d - lastDigit) == 1) {
                                dp[i + 1][tight && (d == limit)][d] = (dp[i + 1][tight && (d == limit)][d] + dp[i][tight][lastDigit]) % MOD;
                            }
                        }
                    }
                }
            }

            int total = 0;
            for (int tight = 0; tight <= 1; ++tight) {
                for (int d = 0; d <= 9; ++d) {
                    total = (total + dp[n][tight][d]) % MOD;
                }
            }
            return total;
        };

        auto subtractOne = [](string& num) {
            int n = num.size();
            int i = n - 1;
            while (i >= 0 && num[i] == '0') {
                num[i] = '9';
                --i;
            }
            if (i >= 0) {
                num[i]--;
            }
        };

        int countHigh = dpCount(high);
        subtractOne(low);
        int countLow = low.empty() ? 0 : dpCount(low);

        return (countHigh - countLow + MOD) % MOD;          
    }
};
