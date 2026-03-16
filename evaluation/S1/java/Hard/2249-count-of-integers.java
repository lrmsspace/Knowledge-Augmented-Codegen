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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int mod = (int)1e9 + 7;
    private int dfs(char[] num, int index, boolean tight, int sum, int min_sum, int max_sum, Integer[][][] memo) {
        if (index == num.length) {
            return (sum >= min_sum && sum <= max_sum) ? 1 : 0;
        }
        if (memo[index][tight ? 1 : 0][sum] != null) {
            return memo[index][tight ? 1 : 0][sum];
        }

        int limit = tight ? (num[index] - '0') : 9;
        int totalWays = 0;
        for (int digit = 0; digit <= limit; digit++) {
            boolean newTight = tight && (digit == limit);
            totalWays = (totalWays + dfs(num, index + 1, newTight, sum + digit, min_sum, max_sum, memo)) % mod;
        }

        memo[index][tight ? 1 : 0][sum] = totalWays;
        return totalWays;
    }
    private int countUpTo(String num, int min_sum, int max_sum, int mod) {
        char[] numArr = num.toCharArray();
        Integer[][][] memo = new Integer[numArr.length][2][max_sum + 1];
        return dfs(numArr, 0, true, 0, min_sum, max_sum, memo);
    }
    private boolean isGood(String num, int min_sum, int max_sum) {
        int sum = 0;
        for (char ch : num.toCharArray()) {
            sum += (ch - '0');
        }
        return sum >= min_sum && sum <= max_sum;
    }
    public int count(String num1, String num2, int min_sum, int max_sum) {
        int mod = (int)1e9 + 7;
        return (countUpTo(num2, min_sum, max_sum, mod) - countUpTo(num1, min_sum, max_sum, mod)
                + (isGood(num1, min_sum, max_sum) ? 1 : 0) + mod) % mod;            
    }
}
