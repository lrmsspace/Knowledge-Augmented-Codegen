# Source: https://leetcode.com/problems/count-vowels-permutation/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
#
#
# 	Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
# 	Each vowel 'a' may only be followed by an 'e'.
# 	Each vowel 'e' may only be followed by an 'a' or an 'i'.
# 	Each vowel 'i' may not be followed by another 'i'.
# 	Each vowel 'o' may only be followed by an 'i' or a 'u'.
# 	Each vowel 'u' may only be followed by an 'a'.
#
#
# Since the answer may be too large, return it modulo 10^9 + 7.
#
# Example:
# Input: n = 1
# Output: 5
# Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
#
# Constraints:
# 1 <= n <= 2 * 10^4
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# - Suffix Automaton (graph, tree, string, recursion)
#   • When to use: When needing to efficiently represent all substrings of a string and perform various string operations like counting occurrences, finding distinct substrings, or pattern matching. It is particularly useful for problems involving properties of all substrings or suffixes.
#   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that accepts all suffixes of a given string. It efficiently encodes all substrings and their occurrences, typically constructed in O(N) time and space for a string of length N.
#   • Invariants: Each state in the automaton corresponds to a unique endpos set.; All substrings represented by a state are suffixes of the longest string in that state's endpos set.
#   • Tips: Understand the endpos equivalence classes and suffix links.; Construction is typically incremental, character by character.
#   • Pitfalls: Complexity of implementation can be high due to many edge cases.; Incorrectly handling suffix links during construction.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countVowelPermutation(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        # dp[i][j] 表示长度为 i 的字符串以 j 结尾的数量，j 对应 a,e,i,o,u 分别为 0,1,2,3,4
        dp = [[0] * 5 for _ in range(n + 1)]
        
        # 初始化长度为 1 的字符串
        for j in range(5):
            dp[1][j] = 1
        
        for i in range(2, n + 1):
            dp[i][0] = (dp[i-1][1] + dp[i-1][2] + dp[i-1][4]) % MOD  # a 后面可以接 e,i,u
            dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % MOD              # e 后面可以接 a,i
            dp[i][2] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][3] + dp[i-1][4]) % MOD  # i 后面可以接 a,e,o,u
            dp[i][3] = (dp[i-1][2] + dp[i-1][4]) % MOD              # o 后面可以接 i,u
            dp[i][4] = (dp[i-1][0]) % MOD                            # u 后面可以接 a
        
        return sum(dp[n]) % MOD