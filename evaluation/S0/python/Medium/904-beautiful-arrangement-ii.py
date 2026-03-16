# Source: https://leetcode.com/problems/beautiful-arrangement-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given two integers n and k, construct a list answer that contains n different positive integers ranging from 1 to n and obeys the following requirement:
#
#
# 	Suppose this list is answer = [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.
#
#
# Return the list answer. If there multiple valid answers, return any of them.
#
# Example:
# Input: n = 3, k = 1
# Output: [1,2,3]
# Explanation: The [1,2,3] has three different positive integers ranging from 1 to 3, and the [1,1] has exactly 1 distinct integer: 1
#
# Constraints:
# 1 <= k < n <= 104
#

class Solution(object):
    def constructArray(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[int]
        """
        result = []
        left, right = 1, k + 1
        
        # Create the first k+1 elements with alternating differences
        for i in range(k + 1):
            if i % 2 == 0:
                result.append(left)
                left += 1
            else:
                result.append(right)
                right -= 1
        
        # Append the remaining elements in ascending order
        for i in range(k + 2, n + 1):
            result.append(i)
        
        return result