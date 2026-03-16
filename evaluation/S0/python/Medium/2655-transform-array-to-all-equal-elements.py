# Source: https://leetcode.com/problems/transform-array-to-all-equal-elements/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of size n containing only 1 and -1, and an integer k.
#
# You can perform the following operation at most k times:
#
#
# 	
# 	Choose an index i (0 <= i < n - 1), and multiply both nums[i] and nums[i + 1] by -1.
# 	
#
#
# Note that you can choose the same index i more than once in different operations.
#
# Return true if it is possible to make all elements of the array equal after at most k operations, and false otherwise.
#
# Example:
# Input: nums = [1,-1,1,-1,1], k = 3
#
# Output: true
#
# Explanation:
#
# We can make all elements in the array equal in 2 operations as follows:
#
#
# 	Choose index i = 1, and multiply both nums[1] and nums[2] by -1. Now nums = [1,1,-1,-1,1].
# 	Choose index i = 2, and multiply both nums[2] and nums[3] by -1. Now nums = [1,1,1,1,1].
#
# Constraints:
# 1 <= n == nums.length <= 105
# 	nums[i] is either -1 or 1.
# 	1 <= k <= n
#

class Solution(object):
    def canMakeEqual(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        count_neg = nums.count(-1)
        if count_neg % 2 == 0:
            return count_neg // 2 <= k
        else:
            return (count_neg // 2 + 1) <= k