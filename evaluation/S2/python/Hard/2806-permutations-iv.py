# Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
#
# Problem Description:
# Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
#
# Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
#
# Example:
# Input: n = 4, k = 6
#
# Output: [3,4,1,2]
#
# Explanation:
#
# The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
#
#
# 	[1, 2, 3, 4]
# 	[1, 4, 3, 2]
# 	[2, 1, 4, 3]
# 	[2, 3, 4, 1]
# 	[3, 2, 1, 4]
# 	[3, 4, 1, 2] ← 6th permutation
# 	[4, 1, 2, 3]
# 	[4, 3, 2, 1]
#
#
# Since k = 6, we return [3, 4, 1, 2].
#
# Constraints:
# 1 <= n <= 100
# 	1 <= k <= 1015
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def permute(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[int]
        """
        from math import factorial
        
        # Separate odd and even numbers
        odd_numbers = [i for i in range(1, n + 1) if i % 2 == 1]
        even_numbers = [i for i in range(1, n + 1) if i % 2 == 0]
        
        # Calculate the number of alternating permutations
        num_odd = len(odd_numbers)
        num_even = len(even_numbers)
        
        if abs(num_odd - num_even) > 1:
            return []  # No valid alternating permutations
        
        # Determine the pattern of the alternating permutation
        if num_odd >= num_even:
            pattern = [0, 1] * num_even + [0] * (num_odd - num_even)
        else:
            pattern = [1, 0] * num_odd + [1] * (num_even - num_odd)
        
        # Calculate the total number of alternating permutations
        total_permutations = factorial(num_odd) * factorial(num_even)
        
        if k > total_permutations:
            return []  # k is larger than the total number of permutations
        
        # Generate the k-th permutation using a similar approach to "k-th permutation" problem
        result = []
        k -= 1  # Convert to zero-based index
        
        for p in pattern:
            if p == 0:  # Odd number
                factorial_count = factorial(len(odd_numbers) - 1) * factorial(len(even_numbers))
                index = k // factorial_count
                result.append(odd_numbers[index])
                odd_numbers.pop(index)
                k %= factorial_count
            else:  # Even number
                factorial_count = factorial(len(odd_numbers)) * factorial(len(even_numbers) - 1)
                index = k // factorial_count
                result.append(even_numbers[index])
                even_numbers.pop(index)
                k %= factorial_count
        
        return result