# Source: https://leetcode.com/problems/ant-on-the-boundary/   |   Difficulty: Easy
#
# Problem Description:
# An ant is on a boundary. It sometimes goes left and sometimes right.
#
# You are given an array of non-zero integers nums. The ant starts reading nums from the first element of it to its end. At each step, it moves according to the value of the current element:
#
#
# 	If nums[i] < 0, it moves left by -nums[i] units.
# 	If nums[i] > 0, it moves right by nums[i] units.
#
#
# Return the number of times the ant returns to the boundary.
#
# Example:
# Input: nums = [2,3,-5]
# Output: 1
# Explanation: After the first step, the ant is 2 steps to the right of the boundary.
# After the second step, the ant is 5 steps to the right of the boundary.
# After the third step, the ant is on the boundary.
# So the answer is 1.
#
# Constraints:
# 1 <= nums.length <= 100
# 	-10 <= nums[i] <= 10
# 	nums[i] != 0
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def returnToBoundaryCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        position = 0
        return_count = 0
        
        for move in nums:
            position += move
            if position == 0:
                return_count += 1
                
        return return_count