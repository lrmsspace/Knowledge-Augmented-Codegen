# Source: https://leetcode.com/problems/verbal-arithmetic-puzzle/   |   Difficulty: Hard
#
# Problem Description:
# Given an equation, represented by words on the left side and the result on the right side.
#
# You need to check if the equation is solvable under the following rules:
#
#
# 	Each character is decoded as one digit (0 - 9).
# 	No two characters can map to the same digit.
# 	Each words[i] and result are decoded as one number without leading zeros.
# 	Sum of numbers on the left side (words) will equal to the number on the right side (result).
#
#
# Return true if the equation is solvable, otherwise return false.
#
# Example:
# Input: words = ["SEND","MORE"], result = "MONEY"
# Output: true
# Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
# Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
#
# Constraints:
# 2 <= words.length <= 5
# 	1 <= words[i].length, result.length <= 7
# 	words[i], result contain only uppercase English letters.
# 	The number of different characters used in the expression is at most 10.
#

class Solution(object):
    def isSolvable(self, words, result):
        """
        :type words: List[str]
        :type result: str
        :rtype: bool
        """
        from collections import defaultdict

        char_set = set()
        leading_chars = set()
        char_weight = defaultdict(int)

        for word in words:
            leading_chars.add(word[0])
            for i, ch in enumerate(reversed(word)):
                char_set.add(ch)
                char_weight[ch] += 10 ** i

        leading_chars.add(result[0])
        for i, ch in enumerate(reversed(result)):
            char_set.add(ch)
            char_weight[ch] -= 10 ** i

        char_list = list(char_set)
        n = len(char_list)

        def backtrack(index, used_digits, current_sum):
            if index == n:
                return current_sum == 0

            ch = char_list[index]
            weight = char_weight[ch]

            for digit in range(10):
                if digit in used_digits:
                    continue
                if digit == 0 and ch in leading_chars:
                    continue

                used_digits.add(digit)
                if backtrack(index + 1, used_digits, current_sum + weight * digit):
                    return True
                used_digits.remove(digit)

            return False

        return backtrack(0, set(), 0)