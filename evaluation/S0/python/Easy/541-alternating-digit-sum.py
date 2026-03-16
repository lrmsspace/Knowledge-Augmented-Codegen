# Source: https://leetcode.com/problems/alternating-digit-sum/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer n. Each digit of n has a sign according to the following rules:
#
#
# 	The most significant digit is assigned a positive sign.
# 	Each other digit has an opposite sign to its adjacent digits.
#
#
# Return the sum of all digits with their corresponding sign.
#
# Example:
# Input: n = 521
# Output: 4
# Explanation: (+5) + (-2) + (+1) = 4.
#
# Constraints:
# 1 <= n <= 109
#
#
#  
# .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
# }
# .spoiler {overflow:hidden;}
# .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
# .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
# .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
#

class Solution(object):
    def alternateDigitSum(self, n):
        """
        :type n: int
        :rtype: int
        """
        s = str(n)
        total = 0
        for i, digit in enumerate(s):
            if i % 2 == 0:
                total += int(digit)
            else:
                total -= int(digit)
        return total