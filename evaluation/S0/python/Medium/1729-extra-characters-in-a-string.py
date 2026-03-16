# Source: https://leetcode.com/problems/extra-characters-in-a-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed string s and a dictionary of words dictionary. You have to break s into one or more non-overlapping substrings such that each substring is present in dictionary. There may be some extra characters in s which are not present in any of the substrings.
#
# Return the minimum number of extra characters left over if you break up s optimally.
#
# Example:
# Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
# Output: 1
# Explanation: We can break s in two substrings: "leet" from index 0 to 3 and "code" from index 5 to 8. There is only 1 unused character (at index 4), so we return 1.
#
# Constraints:
# 1 <= s.length <= 50
# 	1 <= dictionary.length <= 50
# 	1 <= dictionary[i].length <= 50
# 	dictionary[i] and s consists of only lowercase English letters
# 	dictionary contains distinct words
#

class Solution(object):
    def minExtraChar(self, s, dictionary):
        """
        :type s: str
        :type dictionary: List[str]
        :rtype: int
        """
        n = len(s)
        dp = [0] * (n + 1)

        for i in range(n - 1, -1, -1):
            dp[i] = dp[i + 1] + 1  # Assume the current character is extra
            for word in dictionary:
                word_len = len(word)
                if s.startswith(word, i):
                    dp[i] = min(dp[i], dp[i + word_len])

        return dp[0]