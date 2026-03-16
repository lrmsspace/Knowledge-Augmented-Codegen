# Source: https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:
#
#
# 	Characters ('a' to 'i') are represented by ('1' to '9') respectively.
# 	Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
#
#
# Return the string formed after mapping.
#
# The test cases are generated so that a unique mapping will always exist.
#
# Example:
# Input: s = "10#11#12"
# Output: "jkab"
# Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
#
# Constraints:
# 1 <= s.length <= 1000
# 	s consists of digits and the '#' letter.
# 	s will be a valid string such that mapping is always possible.
#

class Solution(object):
    def freqAlphabets(self, s):
        """
        :type s: str
        :rtype: str
        """
        i = 0
        result = []
        
        while i < len(s):
            if i + 2 < len(s) and s[i + 2] == '#':
                num = int(s[i:i + 2])
                result.append(chr(num + 96))  # 'a' is 97 in ASCII
                i += 3
            else:
                num = int(s[i])
                result.append(chr(num + 96))
                i += 1
        
        return ''.join(result)