# Source: https://leetcode.com/problems/k-diff-pairs-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
#
# A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
#
#
# 	0 <= i, j < nums.length
# 	i != j
# 	|nums[i] - nums[j]| == k
#
#
# Notice that |val| denotes the absolute value of val.
#
# Example:
# Input: nums = [3,1,4,1,5], k = 2
# Output: 2
# Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
# Although we have two 1s in the input, we should only return the number of unique pairs.
#
# Constraints:
# 1 <= nums.length <= 104
# 	-107 <= nums[i] <= 107
# 	0 <= k <= 107
#

class Solution(object):
    def findPairs(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        if k < 0:
            return 0
        
        num_count = {}
        for num in nums:
            num_count[num] = num_count.get(num, 0) + 1
        
        result = 0
        for num in num_count:
            if k == 0:
                if num_count[num] > 1:
                    result += 1
            else:
                if num + k in num_count:
                    result += 1
        
        return result