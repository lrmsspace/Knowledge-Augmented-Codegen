# Source: https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer num. You will apply the following steps to num two separate times:
#
#
# 	Pick a digit x (0 <= x <= 9).
# 	Pick another digit y (0 <= y <= 9). Note y can be equal to x.
# 	Replace all the occurrences of x in the decimal representation of num by y.
#
#
# Let a and b be the two results from applying the operation to num independently.
#
# Return the max difference between a and b.
#
# Note that neither a nor b may have any leading zeros, and must not be 0.
#
# Example:
# Input: num = 555
# Output: 888
# Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
# The second time pick x = 5 and y = 1 and store the new integer in b.
# We have now a = 999 and b = 111 and max difference = 888
#
# Constraints:
# 1 <= num <= 108
#

class Solution(object):
    def maxDiff(self, num):
        """
        :type num: int
        :rtype: int
        """
        num_str = str(num)

        # 最大值转换
        max_num_str = num_str
        for digit in num_str:
            if digit != '9':
                max_num_str = max_num_str.replace(digit, '9')
                break

        # 最小值转换
        min_num_str = num_str
        if num_str[0] != '1':
            min_num_str = min_num_str.replace(num_str[0], '1')
        else:
            for digit in num_str[1:]:
                if digit != '0' and digit != '1':
                    min_num_str = min_num_str.replace(digit, '0')
                    break

        return int(max_num_str) - int(min_num_str)