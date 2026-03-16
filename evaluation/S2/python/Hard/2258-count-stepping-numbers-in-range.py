# Source: https://leetcode.com/problems/count-stepping-numbers-in-range/   |   Difficulty: Hard
#
# Problem Description:
# Given two positive integers low and high represented as strings, find the count of stepping numbers in the inclusive range [low, high].
#
# A stepping number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
#
# Return an integer denoting the count of stepping numbers in the inclusive range [low, high]. 
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note: A stepping number should not have a leading zero.
#
# Example:
# Input: low = "1", high = "11"
# Output: 10
# Explanation: The stepping numbers in the range [1,11] are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10. There are a total of 10 stepping numbers in the range. Hence, the output is 10.
#
# Constraints:
# 1 <= int(low) <= int(high) < 10100
# 	1 <= low.length, high.length <= 100
# 	low and high consist of only digits.
# 	low and high don't have any leading zeros.
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - String Hashing (string, number, hashing, prefix-sum)
#   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
#   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
#   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
#   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
#   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
# - Fibonacci Numbers (number, recursion, binary-lifting)
#   • When to use: Use when computing the N-th Fibonacci number for extremely large N, or when the result needs to be calculated modulo a specific value, requiring logarithmic time complexity.
#   • Idea: This method computes the N-th Fibonacci number by leveraging matrix exponentiation or specific doubling identities, reducing the problem size by half in each step. It achieves an O(log N) time complexity.
#   • Invariants: The function `compute(n)` always returns the pair `(F_n, F_{n+1})`.; For any `k`, the values `F_k` and `F_{k+1}` are correctly computed before deriving `F_{2k}` and `F_{2k+1}`.
#   • Tips: Utilize matrix exponentiation for a general and robust approach.; The doubling identities F_2k+1 and F_2k can be faster than explicit matrix multiplication.
#   • Pitfalls: Integer overflow if modulo arithmetic or arbitrary-precision integers are not used for large N.; Incorrectly defining base cases in the recursive implementation can lead to errors.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countSteppingNumbers(self, low, high):
        """
        :type low: str
        :type high: str
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def count_stepping_numbers(num):
            s = str(num)
            n = len(s)
            dp = [[[-1 for _ in range(2)] for _ in range(2)] for _ in range(n)]
            
            def dfs(i, tight, leading_zero):
                if i == n:
                    return 1
                if dp[i][tight][leading_zero] != -1:
                    return dp[i][tight][leading_zero]
                
                limit = int(s[i]) if tight else 9
                total = 0
                
                for digit in range(limit + 1):
                    if leading_zero and digit == 0:
                        total += dfs(i + 1, tight and digit == limit, True)
                    elif not leading_zero:
                        if abs(digit - int(s[i - 1])) == 1:
                            total += dfs(i + 1, tight and digit == limit, False)
                
                dp[i][tight][leading_zero] = total % MOD
                return dp[i][tight][leading_zero]
            
            return dfs(0, True, True)
        
        low_count = count_stepping_numbers(int(low) - 1) if int(low) > 0 else 0
        high_count = count_stepping_numbers(int(high))
        
        return (high_count - low_count) % MOD