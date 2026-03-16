# Source: https://leetcode.com/problems/find-the-maximum-number-of-marked-indices/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums.
#
# Initially, all of the indices are unmarked. You are allowed to make this operation any number of times:
#
#
# 	Pick two different unmarked indices i and j such that 2 * nums[i] <= nums[j], then mark i and j.
#
#
# Return the maximum possible number of marked indices in nums using the above operation any number of times.
#
# Example:
# Input: nums = [3,5,2,4]
# Output: 2
# Explanation: In the first operation: pick i = 2 and j = 1, the operation is allowed because 2 * nums[2] <= nums[1]. Then mark index 2 and 1.
# It can be shown that there's no other valid operation so the answer is 2.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#
#
#  
# .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
# }
# .spoiler {overflow:hidden;}
# .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
# .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
# .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
#

class Solution(object):
    def maxNumOfMarkedIndices(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        n = len(nums)
        left, right = 0, n // 2
        marked = 0

        while left < n // 2 and right < n:
            if nums[left] * 2 <= nums[right]:
                marked += 2
                left += 1
                right += 1
            else:
                right += 1

        return marked