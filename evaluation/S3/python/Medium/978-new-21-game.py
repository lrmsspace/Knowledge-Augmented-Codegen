# Source: https://leetcode.com/problems/new-21-game/   |   Difficulty: Medium
#
# Problem Description:
# Alice plays the following game, loosely based on the card game "21".
#
# Alice starts with 0 points and draws numbers while she has less than k points. During each draw, she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an integer. Each draw is independent and the outcomes have equal probabilities.
#
# Alice stops drawing numbers when she gets k or more points.
#
# Return the probability that Alice has n or fewer points.
#
# Answers within 10-5 of the actual answer are considered accepted.
#
# Example:
# Input: n = 10, k = 1, maxPts = 10
# Output: 1.00000
# Explanation: Alice gets a single card, then stops.
#
# Constraints:
# 0 <= k <= n <= 104
# 	1 <= maxPts <= 104
#
# Helpful references (internal KB):
# - Binomial Coefficients (array, dp-2d)
#   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
#   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
#   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
#   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
#   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
# - Reservoir Sampling (array, randomized, simulation)
#   • When to use: When you need to randomly select a fixed number of items (k) from a stream or a very large dataset of unknown size, ensuring each item has an equal probability of selection in a single pass.
#   • Idea: Reservoir sampling is a randomized algorithm that selects k items from a list containing n items, where n is either a very large or unknown number, ensuring each item has an equal probability of being selected. It processes the input in a single pass with O(N) time complexity and O(k) space complexity.
#   • Invariants: The reservoir always contains exactly k elements.; Any element processed up to the current index `i` has a k/(i+1) probability of being in the reservoir.
#   • Tips: Initialize the reservoir with the first k elements from the stream.; For each subsequent element, generate a random index from 0 to current_stream_index.
#   • Pitfalls: Failing to correctly initialize the reservoir with the first k elements.; Generating random indices outside the valid range [0, current_stream_index] or [0, k-1].
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def new21Game(self, n, k, maxPts):
        """
        :type n: int
        :type k: int
        :type maxPts: int
        :rtype: float
        """
        if k == 0 or n >= k + maxPts:
            return 1.0

        dp = [0.0] * (n + 1)
        dp[0] = 1.0
        window_sum = 1.0

        for i in range(1, n + 1):
            dp[i] = window_sum / maxPts
            if i < k:
                window_sum += dp[i]
            if i >= maxPts:
                window_sum -= dp[i - maxPts]

        return sum(dp[k:])