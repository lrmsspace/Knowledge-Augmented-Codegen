# Source: https://leetcode.com/problems/count-nice-pairs-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums that consists of non-negative integers. Let us define rev(x) as the reverse of the non-negative integer x. For example, rev(123) = 321, and rev(120) = 21. A pair of indices (i, j) is nice if it satisfies all of the following conditions:
#
#
# 	0 <= i < j < nums.length
# 	nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
#
#
# Return the number of nice pairs of indices. Since that number can be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [42,11,1,97]
# Output: 2
# Explanation: The two pairs are:
#  - (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
#  - (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
#

class Solution(object):
    def countNicePairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        count_map = {}
        nice_pair_count = 0
        
        for num in nums:
            rev_num = int(str(num)[::-1])
            diff = num - rev_num
            
            if diff in count_map:
                nice_pair_count = (nice_pair_count + count_map[diff]) % MOD
                count_map[diff] += 1
            else:
                count_map[diff] = 1
        
        return nice_pair_count