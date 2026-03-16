# Source: https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.
#
# Return the total number of ways to partition nums under this condition.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [9,4,1,3,7], k = 4
#
# Output: 6
#
# Explanation:
#
# There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most k = 4:
#
#
# 	[[9], [4], [1], [3], [7]]
# 	[[9], [4], [1], [3, 7]]
# 	[[9], [4], [1, 3], [7]]
# 	[[9], [4, 1], [3], [7]]
# 	[[9], [4, 1], [3, 7]]
# 	[[9], [4, 1, 3], [7]]
#
# Constraints:
# 2 <= nums.length <= 5 * 104
# 	1 <= nums[i] <= 109
# 	0 <= k <= 109
#

class Solution(object):
    def countPartitions(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        
        dp = [0] * (n + 1)
        dp[0] = 1
        
        min_deque = []
        max_deque = []
        left = 0
        
        for right in range(n):
            while min_deque and nums[min_deque[-1]] >= nums[right]:
                min_deque.pop()
            min_deque.append(right)
            
            while max_deque and nums[max_deque[-1]] <= nums[right]:
                max_deque.pop()
            max_deque.append(right)
            
            while nums[max_deque[0]] - nums[min_deque[0]] > k:
                if min_deque[0] == left:
                    min_deque.pop(0)
                if max_deque[0] == left:
                    max_deque.pop(0)
                left += 1
            
            dp[right + 1] = (dp[right + 1] + dp[left]) % MOD
            if right > left:
                dp[right + 1] = (dp[right + 1] + dp[right]) % MOD
        
        return dp[n]