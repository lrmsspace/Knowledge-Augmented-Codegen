# Source: https://leetcode.com/problems/find-the-count-of-numbers-which-are-not-special/   |   Difficulty: Medium
#
# Problem Description:
# You are given 2 positive integers l and r. For any number x, all positive divisors of x except x are called the proper divisors of x.
#
# A number is called special if it has exactly 2 proper divisors. For example:
#
#
# 	The number 4 is special because it has proper divisors 1 and 2.
# 	The number 6 is not special because it has proper divisors 1, 2, and 3.
#
#
# Return the count of numbers in the range [l, r] that are not special.
#
# Example:
# Input: l = 5, r = 7
#
# Output: 3
#
# Explanation:
#
# There are no special numbers in the range [5, 7].
#
# Constraints:
# 1 <= l <= r <= 109
#
# Helpful references (internal KB):
# - Sieve of Eratosthenes (array, sieve, enumeration)
#   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
#   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
#   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
#   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
#   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
#   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
#   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
#   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
#   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def nonSpecialCount(self, l, r):
        """
        :type l: int
        :type r: int
        :rtype: int
        """
        def is_special(x):
            if x < 4:
                return False
            count = 0
            for i in range(1, int(x**0.5) + 1):
                if x % i == 0:
                    if i * i == x:
                        count += 1
                    else:
                        count += 2
                if count > 2:
                    return False
            return count == 2

        special_count = 0
        for num in range(l, r + 1):
            if is_special(num):
                special_count += 1

        return (r - l + 1) - special_count