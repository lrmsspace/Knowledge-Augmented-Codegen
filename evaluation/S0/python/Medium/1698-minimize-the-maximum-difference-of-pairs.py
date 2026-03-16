# Source: https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer p. Find p pairs of indices of nums such that the maximum difference amongst all the pairs is minimized. Also, ensure no index appears more than once amongst the p pairs.
#
# Note that for a pair of elements at the index i and j, the difference of this pair is |nums[i] - nums[j]|, where |x| represents the absolute value of x.
#
# Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to be zero.
#
# Example:
# Input: nums = [10,1,2,7,1,3], p = 2
# Output: 1
# Explanation: The first pair is formed from the indices 1 and 4, and the second pair is formed from the indices 2 and 5. 
# The maximum difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
# 	0 <= p <= (nums.length)/2
#

class Solution(object):
    def minimizeMax(self, nums, p):
        """
        :type nums: List[int]
        :type p: int
        :rtype: int
        """
        nums.sort()
        
        def canFormPairs(maxDiff):
            count = 0
            i = 1
            while i < len(nums):
                if nums[i] - nums[i - 1] <= maxDiff:
                    count += 1
                    i += 2  # Skip the next element as it's already paired
                else:
                    i += 1
            return count >= p
        
        left, right = 0, nums[-1] - nums[0]
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            if canFormPairs(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result