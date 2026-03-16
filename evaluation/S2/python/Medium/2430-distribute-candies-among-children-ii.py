# Source: https://leetcode.com/problems/distribute-candies-among-children-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integers n and limit.
#
# Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
#
# Example:
# Input: n = 5, limit = 2
# Output: 3
# Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
#
# Constraints:
# 1 <= n <= 106
# 	1 <= limit <= 106
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Binomial Coefficients (array, enumeration)
#   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
#   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
#   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
#   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
#   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
# - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
#   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
#   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
#   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
#   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
#   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def distributeCandies(self, n, limit):
        """
        :type n: int
        :type limit: int
        :rtype: int
        """
        # The number of ways to distribute n candies among 3 children with each child getting at most limit candies can be calculated using the principle of inclusion-exclusion.
        # We can first calculate the total number of ways to distribute n candies without any restrictions, which is C(n + 3 - 1, 3 - 1) = C(n + 2, 2).
        # Then we need to subtract the cases where at least one child gets more than limit candies. This can be calculated as:
        # - For one child getting more than limit: C(n - (limit + 1) + 3 - 1, 3 - 1) = C(n - limit + 1, 2)
        # - For two children getting more than limit: C(n - 2 * (limit + 1) + 3 - 1, 3 - 1) = C(n - 2 * limit, 2)
        # - For three children getting more than limit: C(n - 3 * (limit + 1) + 3 - 1, 3 - 1) = C(n - 3 * limit - 1, 2)
        # Finally, we need to add back the cases where two children get more than limit (since they were subtracted twice), and subtract the cases where three children get more than limit (since they were added back once).
        
        def comb(a, b):
            if a < b or b < 0:
                return 0
            if b == 0 or b == a:
                return 1
            if b > a // 2:
                b = a - b
            res = 1
            for i in range(b):
                res = res * (a - i) // (i + 1)
            return res
        
        total_ways = comb(n + 2, 2)
        subtract_one_child = comb(n - limit + 1, 2)
        subtract_two_children = comb(n - 2 * limit, 2)
        subtract_three_children = comb(n - 3 * limit - 1, 2)
        
        result = total_ways - subtract_one_child * 3 + subtract_two_children * 3 - subtract_three_children
        return result