# Source: https://leetcode.com/problems/strong-password-checker-ii/   |   Difficulty: Easy
#
# Problem Description:
# A password is said to be strong if it satisfies all the following criteria:
#
#
# 	It has at least 8 characters.
# 	It contains at least one lowercase letter.
# 	It contains at least one uppercase letter.
# 	It contains at least one digit.
# 	It contains at least one special character. The special characters are the characters in the following string: "!@#$%^&*()-+".
# 	It does not contain 2 of the same character in adjacent positions (i.e., "aab" violates this condition, but "aba" does not).
#
#
# Given a string password, return true if it is a strong password. Otherwise, return false.
#
# Example:
# Input: password = "IloveLe3tcode!"
# Output: true
# Explanation: The password meets all the requirements. Therefore, we return true.
#
# Constraints:
# 1 <= password.length <= 100
# 	password consists of letters, digits, and special characters: "!@#$%^&*()-+".
#

class Solution(object):
    def strongPasswordCheckerII(self, password):
        """
        :type password: str
        :rtype: bool
        """
        if len(password) < 8:
            return False
        
        has_lower = has_upper = has_digit = has_special = False
        special_characters = set("!@#$%^&*()-+")
        
        for i in range(len(password)):
            char = password[i]
            
            if char.islower():
                has_lower = True
            elif char.isupper():
                has_upper = True
            elif char.isdigit():
                has_digit = True
            elif char in special_characters:
                has_special = True
            
            if i > 0 and password[i] == password[i - 1]:
                return False
        
        return has_lower and has_upper and has_digit and has_special