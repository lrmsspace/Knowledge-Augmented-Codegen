# Source: https://leetcode.com/problems/maximum-product-of-two-digits/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer n.
#
# Return the maximum product of any two digits in n.
#
# Note: You may use the same digit twice if it appears more than once in n.
#
# Example:
# Input: n = 31
#
# Output: 3
#
# Explanation:
#
#
# 	The digits of n are [3, 1].
# 	The possible products of any two digits are: 3 * 1 = 3.
# 	The maximum product is 3.
#
# Constraints:
# 10 <= n <= 109
#

class Solution(object):
    def maxProduct(self, n):
        """
        :type n: int
        :rtype: int
        """
        digits = [int(d) for d in str(n)]
        max_product = 0
        
        for i in range(len(digits)):
            for j in range(i, len(digits)):
                product = digits[i] * digits[j]
                if product > max_product:
                    max_product = product
                    
        return max_product