# Source: https://leetcode.com/problems/minimum-deletions-to-make-array-divisible/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integer arrays nums and numsDivide. You can delete any number of elements from nums.
#
# Return the minimum number of deletions such that the smallest element in nums divides all the elements of numsDivide. If this is not possible, return -1.
#
# Note that an integer x divides y if y % x == 0.
#
# Example:
# Input: nums = [2,3,2,4,3], numsDivide = [9,6,9,3,15]
# Output: 2
# Explanation: 
# The smallest element in [2,3,2,4,3] is 2, which does not divide all the elements of numsDivide.
# We use 2 deletions to delete the elements in nums that are equal to 2 which makes nums = [3,4,3].
# The smallest element in [3,4,3] is 3, which divides all the elements of numsDivide.
# It can be shown that 2 is the minimum number of deletions needed.
#
# Constraints:
# 1 <= nums.length, numsDivide.length <= 105
# 	1 <= nums[i], numsDivide[i] <= 109
#
# Helpful references (internal KB):
# - Euclidean algorithm for computing the greatest common divisor (number, gcd)
#   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
#   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
#   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
#   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
#   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Linear Diophantine Equation (number, greedy)
#   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
#   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
#   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
#   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
#   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, nums, numsDivide):
        """
        :type nums: List[int]
        :type numsDivide: List[int]
        :rtype: int
        """
        from math import gcd
        from collections import Counter
        
        # Step 1: Compute the GCD of all elements in numsDivide
        gcd_value = numsDivide[0]
        for num in numsDivide[1:]:
            gcd_value = gcd(gcd_value, num)
        
        # Step 2: Count the frequency of each element in nums
        freq = Counter(nums)
        
        # Step 3: Sort the unique elements in nums
        unique_nums = sorted(freq.keys())
        
        # Step 4: Iterate through the sorted unique elements and check divisibility
        deletions = 0
        for num in unique_nums:
            if gcd_value % num == 0:
                return deletions
            deletions += freq[num]
        
        return -1