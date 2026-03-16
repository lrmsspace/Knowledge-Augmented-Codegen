# Source: https://leetcode.com/problems/minimum-numbers-of-function-calls-to-make-target-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. You have an integer array arr of the same length with all values set to 0 initially. You also have the following modify function:
#
# You want to use the modify function to convert arr to nums using the minimum number of calls.
#
# Return the minimum number of function calls to make nums from arr.
#
# The test cases are generated so that the answer fits in a 32-bit signed integer.
#
# Example:
# Input: nums = [1,5]
# Output: 5
# Explanation: Increment by 1 (second element): [0, 0] to get [0, 1] (1 operation).
# Double all the elements: [0, 1] -> [0, 2] -> [0, 4] (2 operations).
# Increment by 1 (both elements)  [0, 4] -> [1, 4] -> [1, 5] (2 operations).
# Total of operations: 1 + 2 + 2 = 5.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
#

class Solution(object):
    def minOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        increment_ops = 0
        double_ops = 0
        
        for num in nums:
            binary_repr = bin(num)[2:]  # Get binary representation without '0b' prefix
            increment_ops += binary_repr.count('1')  # Count of '1's gives increment operations
            double_ops = max(double_ops, len(binary_repr) - 1)  # Length - 1 gives double operations needed
        
        return increment_ops + double_ops