// Source: https://leetcode.com/problems/count-of-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two numeric strings num1 and num2 and two integers max_sum and min_sum. We denote an integer x to be good if:
//
//
// 	num1 <= x <= num2
// 	min_sum <= digit_sum(x) <= max_sum.
//
//
// Return the number of good integers. Since the answer may be large, return it modulo 109 + 7.
//
// Note that digit_sum(x) denotes the sum of the digits of x.
//
// Example:
// Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
// Output: 11
// Explanation: There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.
//
// Constraints:
// 1 <= num1 <= num2 <= 1022
// 	1 <= min_sum <= max_sum <= 400
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        const int MOD = 1e9 + 7;

        auto digit_sum_dp = [&](const string& num, int limit_sum) {
            int n = num.size();
            // dp[pos][tight][sum] = number of ways
            vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(limit_sum + 1, 0)));
            dp[0][1][0] = 1; // Starting point

            for (int pos = 0; pos < n; ++pos) {
                for (int tight = 0; tight <= 1; ++tight) {
                    for (int sum = 0; sum <= limit_sum; ++sum) {
                        if (dp[pos][tight][sum] == 0) continue;
                        int limit_digit = tight ? (num[pos] - '0') : 9;
                        for (int digit = 0; digit <= limit_digit; ++digit) {
                            int new_tight = (tight && (digit == limit_digit)) ? 1 : 0;
                            int new_sum = sum + digit;
                            if (new_sum <= limit_sum) {
                                dp[pos + 1][new_tight][new_sum] = (dp[pos + 1][new_tight][new_sum] + dp[pos][tight][sum]) % MOD;
                            }
                        }
                    }
                }
            }

            int total_count = 0;
            for (int tight = 0; tight <= 1; ++tight) {
                for (int sum = 0; sum <= limit_sum; ++sum) {
                    total_count = (total_count + dp[n][tight][sum]) % MOD;
                }
            }
            return total_count;
        };

        auto count_up_to = [&](const string& num, int limit_sum) {
            return digit_sum_dp(num, limit_sum);
        };

        auto decrement_string = [](string num) {
            int n = num.size();
            int i = n - 1;
            while (i >= 0 && num[i] == '0') {
                num[i] = '9';
                --i;
            }
            if (i >= 0) {
                num[i]--;
            }
            if (num[0] == '0') {
                num.erase(0, 1);
            }
            return num;
        };

        string prev_num1 = decrement_string(num1);
        int count_num2_max = count_up_to(num2, max_sum);
        int count_num2_min = count_up_to(num2, min_sum - 1);
        int count_num1_max = count_up_to(prev_num1, max_sum);
        int count_num1_min = count_up_to(prev_num1, min_sum - 1);
        int result = (count_num2_max - count_num2_min - (count_num1_max - count_num1_min) + 2 * MOD) % MOD;
        return result;
    }
};
