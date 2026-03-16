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
# - Binomial Coefficients (array, number, dp-1d, mod-exp)
#   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
#   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
#   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
#   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
#   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - Josephus Problem (number, dp-1d, recursion)
#   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
#   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
#   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
#   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
#   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
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
                # Exclude the current element
                dp[i][j] = dp[i - 1][j]
                
                # Include the current element if it does not exceed the sum
                if j >= nums[i - 1]:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % MOD
        
        # The power of all subsequences is the sum of counts of subsequences that sum to k
        power_sum = sum(dp[i][k] for i in range(1, n + 1)) % MOD
        
        return power_sum