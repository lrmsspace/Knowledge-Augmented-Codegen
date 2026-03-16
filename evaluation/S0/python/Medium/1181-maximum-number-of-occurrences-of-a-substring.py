# Source: https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, return the maximum number of occurrences of any substring under the following rules:
#
#
# 	The number of unique characters in the substring must be less than or equal to maxLetters.
# 	The substring size must be between minSize and maxSize inclusive.
#
# Example:
# Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
# Output: 2
# Explanation: Substring "aab" has 2 occurrences in the original string.
# It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
#
# Constraints:
# 1 <= s.length <= 105
# 	1 <= maxLetters <= 26
# 	1 <= minSize <= maxSize <= min(26, s.length)
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def maxFreq(self, s, maxLetters, minSize, maxSize):
        """
        :type s: str
        :type maxLetters: int
        :type minSize: int
        :type maxSize: int
        :rtype: int
        """
        from collections import defaultdict

        substring_count = defaultdict(int)

        for i in range(len(s) - minSize + 1):
            substring = s[i:i + minSize]
            unique_chars = set(substring)

            if len(unique_chars) <= maxLetters:
                substring_count[substring] += 1

        if not substring_count:
            return 0

        return max(substring_count.values())