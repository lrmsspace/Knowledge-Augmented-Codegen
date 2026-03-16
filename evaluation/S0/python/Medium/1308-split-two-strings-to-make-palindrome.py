# Source: https://leetcode.com/problems/split-two-strings-to-make-palindrome/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings a and b of the same length. Choose an index and split both strings at the same index, splitting a into two strings: aprefix and asuffix where a = aprefix + asuffix, and splitting b into two strings: bprefix and bsuffix where b = bprefix + bsuffix. Check if aprefix + bsuffix or bprefix + asuffix forms a palindrome.
#
# When you split a string s into sprefix and ssuffix, either ssuffix or sprefix is allowed to be empty. For example, if s = "abc", then "" + "abc", "a" + "bc", "ab" + "c" , and "abc" + "" are valid splits.
#
# Return true if it is possible to form a palindrome string, otherwise return false.
#
# Notice that x + y denotes the concatenation of strings x and y.
#
# Example:
# Input: a = "x", b = "y"
# Output: true
# Explaination: If either a or b are palindromes the answer is true since you can split in the following way:
# aprefix = "", asuffix = "x"
# bprefix = "", bsuffix = "y"
# Then, aprefix + bsuffix = "" + "y" = "y", which is a palindrome.
#
# Constraints:
# 1 <= a.length, b.length <= 105
# 	a.length == b.length
# 	a and b consist of lowercase English letters
#

class Solution(object):
    def checkPalindromeFormation(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: bool
        """
        def is_palindrome(s, left, right):
            while left < right:
                if s[left] != s[right]:
                    return False
                left += 1
                right -= 1
            return True

        def can_form_palindrome(a, b):
            left, right = 0, len(a) - 1
            while left < right and a[left] == b[right]:
                left += 1
                right -= 1
            return is_palindrome(a, left, right) or is_palindrome(b, left, right)

        return can_form_palindrome(a, b) or can_form_palindrome(b, a)