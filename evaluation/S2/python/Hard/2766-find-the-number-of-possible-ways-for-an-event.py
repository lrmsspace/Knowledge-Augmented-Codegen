# Source: https://leetcode.com/problems/find-the-number-of-possible-ways-for-an-event/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers n, x, and y.
#
# An event is being held for n performers. When a performer arrives, they are assigned to one of the x stages. All performers assigned to the same stage will perform together as a band, though some stages might remain empty.
#
# After all performances are completed, the jury will award each band a score in the range [1, y].
#
# Return the total number of possible ways the event can take place.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note that two events are considered to have been held differently if either of the following conditions is satisfied:
#
#
# 	Any performer is assigned a different stage.
# 	Any band is awarded a different score.
#
# Example:
# Input: n = 1, x = 2, y = 3
#
# Output: 6
#
# Explanation:
#
#
# 	There are 2 ways to assign a stage to the performer.
# 	The jury can award a score of either 1, 2, or 3 to the only band.
#
# Constraints:
# 1 <= n, x, y <= 1000
#
# Helpful references (internal KB):
# - Factorial modulo 
# p (number, counting, recursion)
#   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
#   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
#   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
#   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
#   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Binomial Coefficients (array, number, dp-1d, mod-exp)
#   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
#   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
#   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
#   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
#   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfWays(self, n, x, y):
        """
        :type n: int
        :type x: int
        :type y: int
        :rtype: int
        """
        MOD = 10**9 + 7

        # Step 1: Count the number of ways to assign n performers to x stages
        # This is equivalent to counting the number of ways to partition n performers into at most x non-empty subsets (bands).
        # We can use a dynamic programming approach similar to counting set partitions.

        # dp[i][j] will represent the number of ways to partition i performers into j non-empty subsets
        dp = [[0] * (x + 1) for _ in range(n + 1)]
        dp[0][0] = 1  # Base case: one way to partition zero performers into zero subsets

        for i in range(1, n + 1):
            for j in range(1, min(i, x) + 1):
                dp[i][j] = (dp[i - 1][j - 1] + j * dp[i - 1][j]) % MOD

        # The total ways to assign n performers to x stages is the sum of dp[n][j] for j from 1 to x
        total_assignments = sum(dp[n][j] for j in range(1, x + 1)) % MOD

        # Step 2: Each band can be awarded a score from 1 to y
        # If there are k bands, then there are y^k ways to award scores.
        # We need to sum this over all possible numbers of bands (from 1 to x).

        total_ways = 0
        for k in range(1, x + 1):
            if dp[n][k] > 0:
                total_ways = (total_ways + dp[n][k] * pow(y, k, MOD)) % MOD

        return total_ways