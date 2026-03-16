# Source: https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, you need to partition it into one or more balanced substrings. For example, if s == "ababcc" then ("abab", "c", "c"), ("ab", "abc", "c"), and ("ababcc") are all valid partitions, but ("a", "bab", "cc"), ("aba", "bc", "c"), and ("ab", "abcc") are not. The unbalanced substrings are bolded.
#
# Return the minimum number of substrings that you can partition s into.
#
# Note: A balanced string is a string where each character in the string occurs the same number of times.
#
# Example:
# Input: s = "fabccddg"
#
# Output: 3
#
# Explanation:
#
# We can partition the string s into 3 substrings in one of the following ways: ("fab, "ccdd", "g"), or ("fabc", "cd", "dg").
#
# Constraints:
# 1 <= s.length <= 1000
# 	s consists only of English lowercase letters.
#

class Solution(object):
    def minimumSubstringsInPartition(self, s):
        """
        :type s: str
        :rtype: int
        """
        from collections import Counter

        total_count = Counter(s)
        substr_count = 0
        current_count = Counter()

        for char in s:
            current_count[char] += 1

            if all(current_count[c] * len(total_count) == total_count[c] for c in current_count):
                substr_count += 1
                current_count.clear()

        return substr_count