# Source: https://leetcode.com/problems/minimum-division-operations-to-make-array-non-decreasing/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# Any positive divisor of a natural number x that is strictly less than x is called a proper divisor of x. For example, 2 is a proper divisor of 4, while 6 is not a proper divisor of 6.
#
# You are allowed to perform an operation any number of times on nums, where in each operation you select any one element from nums and divide it by its greatest proper divisor.
#
# Return the minimum number of operations required to make the array non-decreasing.
#
# If it is not possible to make the array non-decreasing using any number of operations, return -1.
#
# Example:
# Input: nums = [25,7]
#
# Output: 1
#
# Explanation:
#
# Using a single operation, 25 gets divided by 5 and nums becomes [5, 7].
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 106
#
# Helpful references (internal KB):
# - Linear Sieve (array, sieve)
#   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
#   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
#   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
#   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
#   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
# - Linear Sieve (array, sieve)
#   • When to use: Use when you need to find all prime numbers up to a given limit N, or compute the least prime factor for all numbers in that range, efficiently in linear time.
#   • Idea: The Linear Sieve finds all prime numbers up to N in O(N) time by ensuring each composite number is marked exactly once by its least prime factor. It also computes the least prime factor for every number up to N.
#   • Invariants: The 'primes' list always contains all prime numbers found so far in increasing order.; lpf[i] stores the least prime factor of 'i' if 'i' is composite, or 'i' itself if 'i' is prime.
#   • Tips: Store the least prime factor (LPF) for each number in an array.; Maintain a dynamically growing list of primes found so far.
#   • Pitfalls: Incorrectly marking multiples can lead to O(N log log N) or worse complexity.; Forgetting to store the least prime factor can break the linear time guarantee.
# - Sieve of Eratosthenes (array, sieve, enumeration)
#   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
#   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
#   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
#   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n <= 1:
            return 0

        # Step 1: Precompute the greatest proper divisor for all numbers up to max(nums)
        max_num = max(nums)
        gcd = [0] * (max_num + 1)
        for i in range(2, max_num + 1):
            for j in range(i * 2, max_num + 1, i):
                gcd[j] = i

        operations = 0
        for i in range(n - 2, -1, -1):
            while nums[i] > nums[i + 1]:
                if gcd[nums[i]] == 0:  # No proper divisor
                    return -1
                nums[i] //= gcd[nums[i]]
                operations += 1

        return operations