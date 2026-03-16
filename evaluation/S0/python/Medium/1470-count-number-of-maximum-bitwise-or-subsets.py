# Source: https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.
#
# An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.
#
# The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).
#
# Example:
# Input: nums = [3,1]
# Output: 2
# Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
# - [3]
# - [3,1]
#
# Constraints:
# 1 <= nums.length <= 16
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def countMaxOrSubsets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_or = 0
        count = 0
        
        n = len(nums)
        
        # Calculate the maximum possible bitwise OR
        for num in nums:
            max_or |= num
        
        # Function to perform backtracking
        def backtrack(index, current_or):
            nonlocal count
            
            if index == n:
                if current_or == max_or:
                    count += 1
                return
            
            # Include the current number
            backtrack(index + 1, current_or | nums[index])
            # Exclude the current number
            backtrack(index + 1, current_or)
        
        backtrack(0, 0)
        
        return count