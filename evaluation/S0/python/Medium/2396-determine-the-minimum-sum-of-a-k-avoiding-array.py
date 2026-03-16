# Source: https://leetcode.com/problems/determine-the-minimum-sum-of-a-k-avoiding-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers, n and k.
#
# An array of distinct positive integers is called a k-avoiding array if there does not exist any pair of distinct elements that sum to k.
#
# Return the minimum possible sum of a k-avoiding array of length n.
#
# Example:
# Input: n = 5, k = 4
# Output: 18
# Explanation: Consider the k-avoiding array [1,2,4,5,6], which has a sum of 18.
# It can be proven that there is no k-avoiding array with a sum less than 18.
#
# Constraints:
# 1 <= n, k <= 50
#

class Solution(object):
    def minimumSum(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        used = set()
        total = 0
        num = 1
        
        while n > 0:
            if (k - num) not in used:
                used.add(num)
                total += num
                n -= 1
            num += 1
        
        return total