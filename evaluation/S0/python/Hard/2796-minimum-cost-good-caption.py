# Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
#
# For example:
#
#
# 	"aaabbb" and "aaaaccc" are good captions.
# 	"aabbb" and "ccccd" are not good captions.
#
#
# You can perform the following operation any number of times:
#
# Choose an index i (where 0 <= i < n) and change the character at that index to either:
#
#
# 	The character immediately before it in the alphabet (if caption[i] != 'a').
# 	The character immediately after it in the alphabet (if caption[i] != 'z').
#
#
# Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
#
# Example:
# Input: caption = "cdcd"
#
# Output: "cccc"
#
# Explanation:
#
# It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
#
#
# 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
# 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
#
#
# Since "cccc" is lexicographically smaller than "dddd", return "cccc".
#
# Constraints:
# 1 <= caption.length <= 5 * 104
# 	caption consists only of lowercase English letters.
#

class Solution(object):
    def minCostGoodCaption(self, caption):
        """
        :type caption: str
        :rtype: str
        """
        n = len(caption)
        dp = [[(float('inf'), '') for _ in range(3)] for _ in range(n + 1)]
        dp[0][0] = (0, '')

        for i in range(1, n + 1):
            for j in range(3):
                for k in range(3):
                    if j + k < 3:
                        continue
                    cost = sum(caption[i - 1 - x] != caption[i - 1] for x in range(j))
                    new_cost = dp[i - j][k][0] + cost
                    new_caption = dp[i - j][k][1] + caption[i - 1] * j
                    if new_cost < dp[i][j][0] or (new_cost == dp[i][j][0] and new_caption < dp[i][j][1]):
                        dp[i][j] = (new_cost, new_caption)

        result = min(dp[n], key=lambda x: (x[0], x[1]))
        return result[1] if result[0] != float('inf') else ''