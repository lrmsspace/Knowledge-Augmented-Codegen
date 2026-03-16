# Source: https://leetcode.com/problems/number-of-squareful-arrays/   |   Difficulty: Hard
#
# Problem Description:
# An array is squareful if the sum of every pair of adjacent elements is a perfect square.
#
# Given an integer array nums, return the number of permutations of nums that are squareful.
#
# Two permutations perm1 and perm2 are different if there is some index i such that perm1[i] != perm2[i].
#
# Example:
# Input: nums = [1,17,8]
# Output: 2
# Explanation: [1,8,17] and [17,8,1] are the valid permutations.
#
# Constraints:
# 1 <= nums.length <= 12
# 	0 <= nums[i] <= 109
#

class Solution(object):
    def numSquarefulPerms(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict
        import math

        def is_perfect_square(x):
            s = int(math.isqrt(x))
            return s * s == x

        n = len(nums)
        graph = defaultdict(list)
        for i in range(n):
            for j in range(n):
                if i != j and is_perfect_square(nums[i] + nums[j]):
                    graph[i].append(j)

        def backtrack(node, visited_count):
            if visited_count == n:
                return 1
            total = 0
            for neighbor in graph[node]:
                if not used[neighbor]:
                    used[neighbor] = True
                    total += backtrack(neighbor, visited_count + 1)
                    used[neighbor] = False
            return total

        total_permutations = 0
        nums.sort()
        for i in range(n):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            used = [False] * n
            used[i] = True
            total_permutations += backtrack(i, 1)

        return total_permutations