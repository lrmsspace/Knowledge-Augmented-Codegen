# Source: https://leetcode.com/problems/pascals-triangle-ii/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.
#
# In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
#
# Example:
# Input: rowIndex = 3
# Output: [1,3,3,1]
#
# Constraints:
# 0 <= rowIndex <= 33
#
#
#  
# Follow up: Could you optimize your algorithm to use only O(rowIndex) extra space?
#

class Solution(object):
    def getRow(self, rowIndex):
        """
        :type rowIndex: int
        :rtype: List[int]
        """
        row = [1] * (rowIndex + 1)
        for i in range(2, rowIndex + 1):
            for j in range(i - 1, 0, -1):
                row[j] += row[j - 1]
        return row