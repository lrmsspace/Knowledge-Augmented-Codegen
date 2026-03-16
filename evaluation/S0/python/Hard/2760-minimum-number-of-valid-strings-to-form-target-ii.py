# Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of strings words and a string target.
#
# A string x is called valid if x is a prefix of any string in words.
#
# Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.
#
# Example:
# Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
#
# Output: 3
#
# Explanation:
#
# The target string can be formed by concatenating:
#
#
# 	Prefix of length 2 of words[1], i.e. "aa".
# 	Prefix of length 3 of words[2], i.e. "bcd".
# 	Prefix of length 3 of words[0], i.e. "abc".
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 5 * 104
# 	The input is generated such that sum(words[i].length) <= 105.
# 	words[i] consists only of lowercase English letters.
# 	1 <= target.length <= 5 * 104
# 	target consists only of lowercase English letters.
#

class Solution(object):
    def minValidStrings(self, words, target):
        """
        :type words: List[str]
        :type target: str
        :rtype: int
        """
        n = len(target)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        prefixes = set()
        for word in words:
            for i in range(1, len(word) + 1):
                prefixes.add(word[:i])

        for i in range(1, n + 1):
            for j in range(i):
                if target[j:i] in prefixes:
                    dp[i] = min(dp[i], dp[j] + 1)

        return dp[n] if dp[n] != float('inf') else -1