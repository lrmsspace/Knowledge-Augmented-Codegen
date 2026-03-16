# Source: https://leetcode.com/problems/largest-number-after-mutating-substring/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string num, which represents a large integer. You are also given a 0-indexed integer array change of length 10 that maps each digit 0-9 to another digit. More formally, digit d maps to digit change[d].
#
# You may choose to mutate a single substring of num. To mutate a substring, replace each digit num[i] with the digit it maps to in change (i.e. replace num[i] with change[num[i]]).
#
# Return a string representing the largest possible integer after mutating (or choosing not to) a single substring of num.
#
# A substring is a contiguous sequence of characters within the string.
#
# Example:
# Input: num = "132", change = [9,8,5,0,3,6,4,2,6,8]
# Output: "832"
# Explanation: Replace the substring "1":
# - 1 maps to change[1] = 8.
# Thus, "132" becomes "832".
# "832" is the largest number that can be created, so return it.
#
# Constraints:
# 1 <= num.length <= 105
# 	num consists of only digits 0-9.
# 	change.length == 10
# 	0 <= change[d] <= 9
#

class Solution(object):
    def maximumNumber(self, num, change):
        """
        :type num: str
        :type change: List[int]
        :rtype: str
        """
        num = list(num)
        n = len(num)
        mutated = False

        for i in range(n):
            digit = int(num[i])
            mapped_digit = change[digit]

            if mapped_digit > digit:
                num[i] = str(mapped_digit)
                mutated = True
            elif mutated and mapped_digit < digit:
                break

        return ''.join(num)