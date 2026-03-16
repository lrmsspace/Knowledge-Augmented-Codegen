# Source: https://leetcode.com/problems/lexicographically-smallest-beautiful-string/   |   Difficulty: Hard
#
# Problem Description:
# A string is beautiful if:
#
#
# 	It consists of the first k letters of the English lowercase alphabet.
# 	It does not contain any substring of length 2 or more which is a palindrome.
#
#
# You are given a beautiful string s of length n and a positive integer k.
#
# Return the lexicographically smallest string of length n, which is larger than s and is beautiful. If there is no such string, return an empty string.
#
# A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b.
#
#
# 	For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
#
# Example:
# Input: s = "abcz", k = 26
# Output: "abda"
# Explanation: The string "abda" is beautiful and lexicographically larger than the string "abcz".
# It can be proven that there is no string that is lexicographically larger than the string "abcz", beautiful, and lexicographically smaller than the string "abda".
#
# Constraints:
# 1 <= n == s.length <= 105
# 	4 <= k <= 26
# 	s is a beautiful string.
#

class Solution(object):
    def smallestBeautifulString(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        n = len(s)
        s = list(s)
        
        for i in range(n - 1, -1, -1):
            for c in range(ord(s[i]) + 1, ord('a') + k):
                s[i] = chr(c)
                if (i >= 1 and s[i] == s[i - 1]) or (i >= 2 and s[i] == s[i - 2]):
                    continue
                
                for j in range(i + 1, n):
                    for nc in range(ord('a'), ord('a') + k):
                        s[j] = chr(nc)
                        if (j >= 1 and s[j] == s[j - 1]) or (j >= 2 and s[j] == s[j - 2]):
                            continue
                        break
                return ''.join(s)
        
        return ""