# Source: https://leetcode.com/problems/maximum-strength-of-a-group/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums representing the score of students in an exam. The teacher would like to form one non-empty group of students with maximal strength, where the strength of a group of students of indices i0, i1, i2, ... , ik is defined as nums[i0] * nums[i1] * nums[i2] * ... * nums[ik​].
#
# Return the maximum strength of a group the teacher can create.
#
# Example:
# Input: nums = [3,-1,-5,2,5,-9]
# Output: 1350
# Explanation: One way to form a group of maximal strength is to group the students at indices [0,2,3,4,5]. Their strength is 3 * (-5) * 2 * 5 * (-9) = 1350, which we can show is optimal.
#
# Constraints:
# 1 <= nums.length <= 13
# 	-9 <= nums[i] <= 9
#

class Solution(object):
    def maxStrength(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        negative_numbers = []
        positive_numbers = []
        zero_count = 0
        
        for num in nums:
            if num > 0:
                positive_numbers.append(num)
            elif num < 0:
                negative_numbers.append(num)
            else:
                zero_count += 1
        
        negative_numbers.sort()
        
        if len(negative_numbers) % 2 != 0:
            if len(negative_numbers) == 1 and len(positive_numbers) == 0:
                if zero_count > 0:
                    return 0
                else:
                    return negative_numbers[0]
            else:
                negative_numbers.pop(0)
        
        result = 1
        
        for num in positive_numbers:
            result *= num
        
        for num in negative_numbers:
            result *= num
        
        return result