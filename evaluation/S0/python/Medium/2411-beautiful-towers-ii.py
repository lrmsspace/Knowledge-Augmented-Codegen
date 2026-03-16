# Source: https://leetcode.com/problems/beautiful-towers-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array maxHeights of n integers.
#
# You are tasked with building n towers in the coordinate line. The ith tower is built at coordinate i and has a height of heights[i].
#
# A configuration of towers is beautiful if the following conditions hold:
#
#
# 	1 <= heights[i] <= maxHeights[i]
# 	heights is a mountain array.
#
#
# Array heights is a mountain if there exists an index i such that:
#
#
# 	For all 0 < j <= i, heights[j - 1] <= heights[j]
# 	For all i <= k < n - 1, heights[k + 1] <= heights[k]
#
#
# Return the maximum possible sum of heights of a beautiful configuration of towers.
#
# Example:
# Input: maxHeights = [5,3,4,1,1]
# Output: 13
# Explanation: One beautiful configuration with a maximum sum is heights = [5,3,3,1,1]. This configuration is beautiful since:
# - 1 <= heights[i] <= maxHeights[i]  
# - heights is a mountain of peak i = 0.
# It can be shown that there exists no other beautiful configuration with a sum of heights greater than 13.
#
# Constraints:
# 1 <= n == maxHeights.length <= 105
# 	1 <= maxHeights[i] <= 109
#

class Solution(object):
    def maximumSumOfHeights(self, maxHeights):
        """
        :type maxHeights: List[int]
        :rtype: int
        """
        n = len(maxHeights)
        left = [0] * n
        right = [0] * n
        
        stack = []
        for i in range(n):
            while stack and maxHeights[stack[-1]] >= maxHeights[i]:
                stack.pop()
            left[i] = stack[-1] if stack else -1
            stack.append(i)
        
        stack = []
        for i in range(n-1, -1, -1):
            while stack and maxHeights[stack[-1]] >= maxHeights[i]:
                stack.pop()
            right[i] = stack[-1] if stack else n
            stack.append(i)
        
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + maxHeights[i]
        
        max_sum = 0
        for i in range(n):
            total = maxHeights[i] * (right[i] - left[i] - 1)
            total += prefix[left[i] + 1]
            total += prefix[n] - prefix[right[i]]
            max_sum = max(max_sum, total)
        
        return max_sum