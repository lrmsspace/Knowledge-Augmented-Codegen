# Source: https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/   |   Difficulty: Hard
#
# Problem Description:
# You have a keyboard layout as shown above in the X-Y plane, where each English uppercase letter is located at some coordinate.
#
#
# 	For example, the letter 'A' is located at coordinate (0, 0), the letter 'B' is located at coordinate (0, 1), the letter 'P' is located at coordinate (2, 3) and the letter 'Z' is located at coordinate (4, 1).
#
#
# Given the string word, return the minimum total distance to type such string using only two fingers.
#
# The distance between coordinates (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.
#
# Note that the initial positions of your two fingers are considered free so do not count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.
#
# Example:
# Input: word = "CAKE"
# Output: 3
# Explanation: Using two fingers, one optimal way to type "CAKE" is: 
# Finger 1 on letter 'C' -> cost = 0 
# Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
# Finger 2 on letter 'K' -> cost = 0 
# Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
# Total distance = 3
#
# Constraints:
# 2 <= word.length <= 300
# 	word consists of uppercase English letters.
#

class Solution(object):
    def minimumDistance(self, word):
        """
        :type word: str
        :rtype: int
        """
        def dist(a, b):
            if a == -1 or b == -1:
                return 0
            x1, y1 = divmod(a, 6)
            x2, y2 = divmod(b, 6)
            return abs(x1 - x2) + abs(y1 - y2)

        n = len(word)
        dp = [[[float('inf')] * 26 for _ in range(26)] for _ in range(n + 1)]
        dp[0][-1][-1] = 0

        for i in range(n):
            c = ord(word[i]) - ord('A')
            for f1 in range(-1, 26):
                for f2 in range(-1, 26):
                    if dp[i][f1][f2] == float('inf'):
                        continue
                    dp[i + 1][c][f2] = min(dp[i + 1][c][f2], dp[i][f1][f2] + dist(f1, c))
                    dp[i + 1][f1][c] = min(dp[i + 1][f1][c], dp[i][f1][f2] + dist(f2, c))

        ans = float('inf')
        for f1 in range(26):
            for f2 in range(26):
                ans = min(ans, dp[n][f1][f2])
        return ans