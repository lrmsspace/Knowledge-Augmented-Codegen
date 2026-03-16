# Source: https://leetcode.com/problems/maximum-equal-frequency/   |   Difficulty: Hard
#
# Problem Description:
# Given an array nums of positive integers, return the longest possible length of an array prefix of nums, such that it is possible to remove exactly one element from this prefix so that every number that has appeared in it will have the same number of occurrences.
#
# If after removing one element there are no remaining elements, it's still considered that every appeared number has the same number of ocurrences (0).
#
# Example:
# Input: nums = [2,2,1,1,5,3,3,5]
# Output: 7
# Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4] = 5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
#
# Constraints:
# 2 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def maxEqualFreq(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = {}
        freq = {}
        res = 0
        maxFreq = 0
        
        for i in range(len(nums)):
            if nums[i] in count:
                freq[count[nums[i]]] -= 1
                count[nums[i]] += 1
            else:
                count[nums[i]] = 1
            
            currFreq = count[nums[i]]
            if currFreq in freq:
                freq[currFreq] += 1
            else:
                freq[currFreq] = 1
            
            maxFreq = max(maxFreq, currFreq)
            
            condition1 = maxFreq == 1
            condition2 = freq[maxFreq] * maxFreq + freq[maxFreq - 1] * (maxFreq - 1) == i + 1 and freq[maxFreq] == 1
            condition3 = freq[maxFreq] * maxFreq + 1 == i + 1 and freq[1] == 1
            
            if condition1 or condition2 or condition3:
                res = i + 1
        
        return res