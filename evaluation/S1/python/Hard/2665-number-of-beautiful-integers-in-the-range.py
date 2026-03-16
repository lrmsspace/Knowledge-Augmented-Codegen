# Source: https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/   |   Difficulty: Hard
#
# Problem Description:
# You are given positive integers low, high, and k.
#
# A number is beautiful if it meets both of the following conditions:
#
#
# 	The count of even digits in the number is equal to the count of odd digits.
# 	The number is divisible by k.
#
#
# Return the number of beautiful integers in the range [low, high].
#
# Example:
# Input: low = 10, high = 20, k = 3
# Output: 2
# Explanation: There are 2 beautiful integers in the given range: [12,18]. 
# - 12 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
# - 18 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
# Additionally we can see that:
# - 16 is not beautiful because it is not divisible by k = 3.
# - 15 is not beautiful because it does not contain equal counts even and odd digits.
# It can be shown that there are only 2 beautiful integers in the given range.
#
# Constraints:
# 0 < low <= high <= 109
# 	0 < k <= 20
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfBeautifulIntegers(self, low, high, k):
        """
        :type low: int
        :type high: int
        :type k: int
        :rtype: int
        """
        def count_beautiful(n):
            if n < 0:
                return 0
            
            s = str(n)
            m = len(s)
            
            # dp[pos][even_count][odd_count][mod] = count of ways
            dp = [[[[0] * k for _ in range(m + 1)] for _ in range(m + 1)] for _ in range(m + 1)]
            dp[0][0][0][0] = 1
            
            for pos in range(m):
                digit_limit = int(s[pos])
                for even_count in range(pos + 1):
                    for odd_count in range(pos + 1):
                        for mod in range(k):
                            if dp[pos][even_count][odd_count][mod] == 0:
                                continue
                            for digit in range(digit_limit + 1):
                                new_even_count = even_count + (digit % 2 == 0)
                                new_odd_count = odd_count + (digit % 2 == 1)
                                new_mod = (mod * 10 + digit) % k
                                dp[pos + 1][new_even_count][new_odd_count][new_mod] += dp[pos][even_count][odd_count][mod]
            
            beautiful_count = 0
            for even_count in range(m + 1):
                for odd_count in range(m + 1):
                    if even_count == odd_count:
                        beautiful_count += dp[m][even_count][odd_count][0]
            
            return beautiful_count
        
        return count_beautiful(high) - count_beautiful(low - 1)