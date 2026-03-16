# Source: https://leetcode.com/problems/the-number-of-beautiful-subsets/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums of positive integers and a positive integer k.
#
# A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.
#
# Return the number of non-empty beautiful subsets of the array nums.
#
# A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
#
# Example:
# Input: nums = [2,4,6], k = 2
# Output: 4
# Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
# It can be proved that there are only 4 beautiful subsets in the array [2,4,6].
#
# Constraints:
# 1 <= nums.length <= 18
# 	1 <= nums[i], k <= 1000
#

class Solution(object):
    def beautifulSubsets(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        mod = 10**9 + 7
        n = len(nums)
        count = 0

        def backtrack(start, subset):
            nonlocal count
            if subset:
                count += 1

            for i in range(start, n):
                if all(abs(nums[i] - x) != k for x in subset):
                    subset.append(nums[i])
                    backtrack(i + 1, subset)
                    subset.pop()

        backtrack(0, [])
        return count