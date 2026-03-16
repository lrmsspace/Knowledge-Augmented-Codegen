# Source: https://leetcode.com/problems/find-the-original-typed-string-ii/   |   Difficulty: Hard
#
# Problem Description:
# Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
#
# You are given a string word, which represents the final output displayed on Alice's screen. You are also given a positive integer k.
#
# Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size at least k.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: word = "aabbccdd", k = 7
#
# Output: 5
#
# Explanation:
#
# The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".
#
# Constraints:
# 1 <= word.length <= 5 * 105
#  word consists only of lowercase English letters.
#  1 <= k <= 2000
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
# - Shortest Paths (array, graph, dp-1d)
#   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
#   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
#   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
#   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
#   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def possibleStringCount(self, word, k):
        """
        :type word: str
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(word)
        
        # dp[i][j] = number of ways to form a valid original string using the first i characters of word with j consecutive characters
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        for i in range(1, n + 1):
            for j in range(1, k + 1):
                if j == 1:
                    dp[i][j] = sum(dp[i - 1]) % MOD
                else:
                    dp[i][j] = dp[i - 1][j - 1] % MOD
            
            # If the current character is the same as the previous one, we can only extend the previous sequences
            if i > 1 and word[i - 1] == word[i - 2]:
                for j in range(2, k + 1):
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD
        
        return sum(dp[n]) % MOD