# Source: https://leetcode.com/problems/find-special-substring-of-length-k/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s and an integer k.
#
# Determine if there exists a substring of length exactly k in s that satisfies the following conditions:
#
#
# 	The substring consists of only one distinct character (e.g., "aaa" or "bbb").
# 	If there is a character immediately before the substring, it must be different from the character in the substring.
# 	If there is a character immediately after the substring, it must also be different from the character in the substring.
#
#
# Return true if such a substring exists. Otherwise, return false.
#
# Example:
# Input: s = "aaabaaa", k = 3
#
# Output: true
#
# Explanation:
#
# The substring s[4..6] == "aaa" satisfies the conditions.
#
#
# 	It has a length of 3.
# 	All characters are the same.
# 	The character before "aaa" is 'b', which is different from 'a'.
# 	There is no character after "aaa".
#
# Constraints:
# 1 <= k <= s.length <= 100
# 	s consists of lowercase English letters only.
#

class Solution(object):
    def hasSpecialSubstring(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: bool
        """
        n = len(s)
        for i in range(n - k + 1):
            substring = s[i:i + k]
            if len(set(substring)) == 1:  # Check if all characters are the same
                before = s[i - 1] if i > 0 else None
                after = s[i + k] if i + k < n else None
                if (before is None or before != substring[0]) and (after is None or after != substring[0]):
                    return True
        return False