# Source: https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/   |   Difficulty: Hard
#
# Problem Description:
# You are given a list of strings of the same length words and a string target.
#
# Your task is to form target using the given words under the following rules:
#
#
# 	target should be formed from left to right.
# 	To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
# 	Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
# 	Repeat the process until you form the string target.
#
#
# Notice that you can use multiple characters from the same string in words provided the conditions above are met.
#
# Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: words = ["acca","bbbb","caca"], target = "aba"
# Output: 6
# Explanation: There are 6 ways to form target.
# "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
# "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
# "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
# "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
# "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
# "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
#
# Constraints:
# 1 <= words.length <= 1000
# 	1 <= words[i].length <= 1000
# 	All strings in words have the same length.
# 	1 <= target.length <= 1000
# 	words[i] and target contain only lowercase English letters.
#

class Solution(object):
    def numWays(self, words, target):
        """
        :type words: List[str]
        :type target: str
        :rtype: int
        """
        MOD = 10**9 + 7
        word_len = len(words[0])
        target_len = len(target)
        
        # Precompute frequency of each character at each position
        freq = [[0] * 26 for _ in range(word_len)]
        for word in words:
            for i, char in enumerate(word):
                freq[i][ord(char) - ord('a')] += 1
        
        # DP array to store number of ways to form target up to index j using first i characters
        dp = [[0] * (target_len + 1) for _ in range(word_len + 1)]
        dp[0][0] = 1  # One way to form empty target
        
        for i in range(1, word_len + 1):
            for j in range(target_len + 1):
                # Not using the i-th character from words
                dp[i][j] = dp[i - 1][j]
                
                if j > 0:
                    char_index = ord(target[j - 1]) - ord('a')
                    dp[i][j] += dp[i - 1][j - 1] * freq[i - 1][char_index]
                    dp[i][j] %= MOD
        
        return dp[word_len][target_len]