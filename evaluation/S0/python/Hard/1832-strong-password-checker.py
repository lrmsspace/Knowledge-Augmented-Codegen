# Source: https://leetcode.com/problems/strong-password-checker/   |   Difficulty: Hard
#
# Problem Description:
# A password is considered strong if the below conditions are all met:
#
#
# 	It has at least 6 characters and at most 20 characters.
# 	It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
# 	It does not contain three repeating characters in a row (i.e., "Baaabb0" is weak, but "Baaba0" is strong).
#
#
# Given a string password, return the minimum number of steps required to make password strong. if password is already strong, return 0.
#
# In one step, you can:
#
#
# 	Insert one character to password,
# 	Delete one character from password, or
# 	Replace one character of password with another character.
#
# Example:
# Input: password = "a"
# Output: 5
#
# Constraints:
# 1 <= password.length <= 50
# 	password consists of letters, digits, dot '.' or exclamation mark '!'.
#

class Solution(object):
    def strongPasswordChecker(self, password):
        """
        :type password: str
        :rtype: int
        """
        missing_type = 3
        if any('a' <= c <= 'z' for c in password):
            missing_type -= 1
        if any('A' <= c <= 'Z' for c in password):
            missing_type -= 1
        if any(c.isdigit() for c in password):
            missing_type -= 1

        change = 0
        one = two = 0
        p = 2
        n = len(password)
        while p < n:
            if password[p] == password[p - 1] == password[p - 2]:
                length = 2
                while p < n and password[p] == password[p - 1]:
                    length += 1
                    p += 1

                change += length // 3
                if length % 3 == 0:
                    one += 1
                elif length % 3 == 1:
                    two += 1
            else:
                p += 1

        if n < 6:
            return max(missing_type, 6 - n)
        elif n <= 20:
            return max(missing_type, change)
        else:
            delete = n - 20
            change -= min(delete, one * 1) // 1
            change -= min(max(delete - one, 0), two * 2) // 2
            change -= max(delete - one - 2 * two, 0) // 3
            return delete + max(missing_type, change)