# Source: https://leetcode.com/problems/find-the-divisibility-array-of-a-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed string word of length n consisting of digits, and a positive integer m.
#
# The divisibility array div of word is an integer array of length n such that:
#
#
# 	div[i] = 1 if the numeric value of word[0,...,i] is divisible by m, or
# 	div[i] = 0 otherwise.
#
#
# Return the divisibility array of word.
#
# Example:
# Input: word = "998244353", m = 3
# Output: [1,1,0,0,0,1,1,0,0]
# Explanation: There are only 4 prefixes that are divisible by 3: "9", "99", "998244", and "9982443".
#
# Constraints:
# 1 <= n <= 105
# 	word.length == n
# 	word consists of digits from 0 to 9
# 	1 <= m <= 109
#

class Solution(object):
    def divisibilityArray(self, word, m):
        """
        :type word: str
        :type m: int
        :rtype: List[int]
        """
        result = []
        current_mod = 0
        
        for char in word:
            digit = int(char)
            current_mod = (current_mod * 10 + digit) % m
            
            if current_mod == 0:
                result.append(1)
            else:
                result.append(0)
        
        return result