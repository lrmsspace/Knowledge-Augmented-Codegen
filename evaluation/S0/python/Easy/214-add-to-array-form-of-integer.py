# Source: https://leetcode.com/problems/add-to-array-form-of-integer/   |   Difficulty: Easy
#
# Problem Description:
# The array-form of an integer num is an array representing its digits in left to right order.
#
#
# 	For example, for num = 1321, the array form is [1,3,2,1].
#
#
# Given num, the array-form of an integer, and an integer k, return the array-form of the integer num + k.
#
# Example:
# Input: num = [1,2,0,0], k = 34
# Output: [1,2,3,4]
# Explanation: 1200 + 34 = 1234
#
# Constraints:
# 1 <= num.length <= 104
# 	0 <= num[i] <= 9
# 	num does not contain any leading zeros except for the zero itself.
# 	1 <= k <= 104
#

class Solution(object):
    def addToArrayForm(self, num, k):
        """
        :type num: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(num)
        carry = 0
        i = n - 1
        
        while k > 0 or carry > 0:
            if i >= 0:
                total = num[i] + (k % 10) + carry
                num[i] = total % 10
                carry = total // 10
                i -= 1
            else:
                total = (k % 10) + carry
                num.insert(0, total % 10)
                carry = total // 10
            
            k //= 10
        
        return num