# Source: https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums of length n and a positive integer k.
#
# The power of an array of integers is defined as the number of subsequences with their sum equal to k.
#
# Return the sum of power of all subsequences of nums.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input:   nums = [1,2,3], k = 3 
#
# Output:   6 
#
# Explanation:
#
# There are 5 subsequences of nums with non-zero power:
#
#
# 	The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
#
#
# Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.
#
# Constraints:
# 1 <= n <= 100
# 	1 <= nums[i] <= 104
# 	1 <= k <= 100
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - Chinese Remainder Theorem (number, recursion, mod-exp)
#   • When to use: When you need to find a unique integer solution that satisfies a system of linear congruences with pairwise coprime moduli. It is used to reconstruct a number from its remainders modulo several divisors.
#   • Idea: The Chinese Remainder Theorem (CRT) finds a unique solution x modulo the product of several pairwise coprime moduli, given a system of congruences. It typically involves computing modular inverses and combining solutions, with a complexity often dominated by modular exponentiation or extended Euclidean algorithm, usually O(N log M) or O(N log(max_modulus)).
#   • Invariants: The current combined solution 'x' satisfies 'x % m_i == a_i' for all congruences '(a_i, m_i)' processed so far.; The current combined modulus 'M' is the product of all individual moduli processed so far.
#   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
#   • Pitfalls: Forgetting to check if moduli are pairwise coprime.; Incorrectly calculating modular inverses.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sumOfPower(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        
        # dp[i][j] will store the count of subsequences of the first i elements that sum to j
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        # Base case: there's one way to sum to 0 (the empty subsequence)
        for i in range(n + 1):
            dp[i][0] = 1
        
        for i in range(1, n + 1):
            for j in range(k + 1):
                dp[i][j] = dp[i - 1][j]  # Exclude the current element
                if j >= nums[i - 1]:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % MOD
        
        # Now we need to calculate the power of all subsequences
        total_power = 0
        for i in range(1, n + 1):
            total_power = (total_power + dp[i][k]) % MOD
        
        return total_power