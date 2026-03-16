# Source: https://leetcode.com/problems/find-the-k-or-of-an-array/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums, and an integer k. Let's introduce K-or operation by extending the standard bitwise OR. In K-or, a bit position in the result is set to 1 if at least k numbers in nums have a 1 in that position.
#
# Return the K-or of nums.
#
# Example:
# Input: nums = [7,12,9,8,9,15], k = 4 
#
# Output: 9 
#
# Explanation: 
#
# Represent numbers in binary:
#
#
# 	
# 		
# 			Number
# 			Bit 3
# 			Bit 2
# 			Bit 1
# 			Bit 0
# 		
# 		
# 			7
# 			0
# 			1
# 			1
# 			1
# 		
# 		
# 			12
# 			1
# 			1
# 			0
# 			0
# 		
# 		
# 			9
# 			1
# 			0
# 			0
# 			1
# 		
# 		
# 			8
# 			1
# 			0
# 			0
# 			0
# 		
# 		
# 			9
# 			1
# 			0
# 			0
# 			1
# 		
# 		
# 			15
# 			1
# 			1
# 			1
# 			1
# 		
# 		
# 			Result = 9
# 			1
# 			0
# 			0
# 			1
# 		
# 	
#
#
# Bit 0 is set in 7, 9, 9, and 15. Bit 3 is set in 12, 9, 8, 9, and 15.
# Only bits 0 and 3 qualify. The result is (1001)2 = 9.
#
# Constraints:
# 1 <= nums.length <= 50
# 	0 <= nums[i] < 231
# 	1 <= k <= nums.length
#

class Solution(object):
    def findKOr(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        bit_count = [0] * 31  # Since nums[i] < 2^31

        # Count the number of 1s in each bit position
        for num in nums:
            for i in range(31):
                if num & (1 << i):
                    bit_count[i] += 1

        result = 0
        # Set bits in the result where the count is at least k
        for i in range(31):
            if bit_count[i] >= k:
                result |= (1 << i)

        return result