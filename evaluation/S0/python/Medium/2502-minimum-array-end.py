# Source: https://leetcode.com/problems/minimum-array-end/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers n and x. You have to construct an array of positive integers nums of size n where for every 0 <= i < n - 1, nums[i + 1] is greater than nums[i], and the result of the bitwise AND operation between all elements of nums is x.
#
# Return the minimum possible value of nums[n - 1].
#
# Example:
# Input: n = 3, x = 4
#
# Output: 6
#
# Explanation:
#
# nums can be [4,5,6] and its last element is 6.
#
# Constraints:
# 1 <= n, x <= 108
#

class Solution(object):
    def minEnd(self, n, x):
        """
        :type n: int
        :type x: int
        :rtype: int
        """
        if n == 1:
            return x
        
        # Find the smallest number greater than x with at least n distinct numbers
        # that can be formed by incrementing from x
        last_num = x
        count = 1  # Count of distinct numbers starting from x
        
        while count < n:
            last_num += 1
            if (last_num & x) == x:
                count += 1
        
        return last_num