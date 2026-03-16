# Source: https://leetcode.com/problems/majority-element-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
#
# Example:
# Input: nums = [3,2,3]
# Output: [3]
#
# Constraints:
# 1 <= nums.length <= 5 * 104
# 	-109 <= nums[i] <= 109
#
#
#  
# Follow up: Could you solve the problem in linear time and in O(1) space?
#

class Solution(object):
    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        if not nums:
            return []

        # Step 1: Find potential candidates
        candidate1, candidate2 = None, None
        count1, count2 = 0, 0

        for num in nums:
            if candidate1 == num:
                count1 += 1
            elif candidate2 == num:
                count2 += 1
            elif count1 == 0:
                candidate1, count1 = num, 1
            elif count2 == 0:
                candidate2, count2 = num, 1
            else:
                count1 -= 1
                count2 -= 1

        # Step 2: Verify the candidates
        result = []
        threshold = len(nums) // 3
        for candidate in (candidate1, candidate2):
            if nums.count(candidate) > threshold:
                result.append(candidate)

        return result