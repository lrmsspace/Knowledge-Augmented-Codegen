# Source: https://leetcode.com/problems/integer-to-english-words/   |   Difficulty: Hard
#
# Problem Description:
# Convert a non-negative integer num to its English words representation.
#
# Example:
# Input: num = 123
# Output: "One Hundred Twenty Three"
#
# Constraints:
# 0 <= num <= 231 - 1
#

class Solution(object):
    def numberToWords(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return "Zero"

        below_20 = ["", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"]
        tens = ["", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"]
        thousands = ["", "Thousand", "Million", "Billion"]

        def helper(n):
            if n == 0:
                return ""
            elif n < 20:
                return below_20[n] + " "
            elif n < 100:
                return tens[n // 10] + " " + helper(n % 10)
            else:
                return below_20[n // 100] + " Hundred " + helper(n % 100)

        result = ""
        for i in range(len(thousands)):
            if num % 1000 != 0:
                result = helper(num % 1000) + thousands[i] + " " + result
            num //= 1000

        return result.strip()