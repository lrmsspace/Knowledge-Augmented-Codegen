# Source: https://leetcode.com/problems/ambiguous-coordinates/   |   Difficulty: Medium
#
# Problem Description:
# We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". Then, we removed all commas, decimal points, and spaces and ended up with the string s.
#
#
# 	For example, "(1, 3)" becomes s = "(13)" and "(2, 0.5)" becomes s = "(205)".
#
#
# Return a list of strings representing all possibilities for what our original coordinates could have been.
#
# Our original representation never had extraneous zeroes, so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other number that can be represented with fewer digits. Also, a decimal point within a number never occurs without at least one digit occurring before it, so we never started with numbers like ".1".
#
# The final answer list can be returned in any order. All coordinates in the final answer have exactly one space between them (occurring after the comma.)
#
# Example:
# Input: s = "(123)"
# Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
#
# Constraints:
# 4 <= s.length <= 12
# 	s[0] == '(' and s[s.length - 1] == ')'.
# 	The rest of s are digits.
#

class Solution(object):
    def ambiguousCoordinates(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        def generate_possible_numbers(s):
            n = len(s)
            if n == 0 or (n > 1 and s[0] == '0' and s[-1] == '0'):
                return []
            if n == 1 or s[0] != '0':
                res = [s]
            else:
                res = []
            for i in range(1, n):
                left, right = s[:i], s[i:]
                if (left[0] == '0' and len(left) > 1) or (right[-1] == '0'):
                    continue
                res.append(left + '.' + right)
            return res

        s = s[1:-1]
        result = []
        for i in range(1, len(s)):
            left_part = s[:i]
            right_part = s[i:]
            left_numbers = generate_possible_numbers(left_part)
            right_numbers = generate_possible_numbers(right_part)
            for left in left_numbers:
                for right in right_numbers:
                    result.append(f"({left}, {right})")
        return result