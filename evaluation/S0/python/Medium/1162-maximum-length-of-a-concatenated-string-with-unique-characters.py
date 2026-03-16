# Source: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
#
# Return the maximum possible length of s.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: arr = ["un","iq","ue"]
# Output: 4
# Explanation: All the valid concatenations are:
# - ""
# - "un"
# - "iq"
# - "ue"
# - "uniq" ("un" + "iq")
# - "ique" ("iq" + "ue")
# Maximum length is 4.
#
# Constraints:
# 1 <= arr.length <= 16
# 	1 <= arr[i].length <= 26
# 	arr[i] contains only lowercase English letters.
#

class Solution(object):
    def maxLength(self, arr):
        """
        :type arr: List[str]
        :rtype: int
        """
        def is_unique(s):
            return len(s) == len(set(s))

        def backtrack(start, path):
            if is_unique(path):
                self.max_len = max(self.max_len, len(path))
            else:
                return

            for i in range(start, len(arr)):
                backtrack(i + 1, path + arr[i])

        self.max_len = 0
        backtrack(0, "")
        return self.max_len