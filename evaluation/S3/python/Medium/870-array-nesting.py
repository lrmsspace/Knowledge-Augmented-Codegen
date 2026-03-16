# Source: https://leetcode.com/problems/array-nesting/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n where nums is a permutation of the numbers in the range [0, n - 1].
#
# You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... } subjected to the following rule:
#
#
# 	The first element in s[k] starts with the selection of the element nums[k] of index = k.
# 	The next element in s[k] should be nums[nums[k]], and then nums[nums[nums[k]]], and so on.
# 	We stop adding right before a duplicate element occurs in s[k].
#
#
# Return the longest length of a set s[k].
#
# Example:
# Input: nums = [5,4,0,3,1,6,2]
# Output: 4
# Explanation: 
# nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
# One of the longest sets s[k]:
# s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] < nums.length
# 	All the values of nums are unique.
#
# Helpful references (internal KB):
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
#   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
#   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
#   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
#   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
#   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
# - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
#   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
#   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
#   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
#   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
#   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def arrayNesting(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        visited = [False] * len(nums)
        max_size = 0

        for i in range(len(nums)):
            if not visited[i]:
                size = 0
                current = i

                while not visited[current]:
                    visited[current] = True
                    current = nums[current]
                    size += 1

                max_size = max(max_size, size)

        return max_size