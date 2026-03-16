# Source: https://leetcode.com/problems/string-compression-ii/   |   Difficulty: Hard
#
# Problem Description:
# Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".
#
# Notice that in this problem, we are not adding '1' after single characters.
#
# Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.
#
# Find the minimum length of the run-length encoded version of s after deleting at most k characters.
#
# Example:
# Input: s = "aaabcccd", k = 2
# Output: 4
# Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6. Deleting any of the characters 'a' or 'c' would at most decrease the length of the compressed string to 5, for instance delete 2 'a' then we will have s = "abcccd" which compressed is abc3d. Therefore, the optimal way is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of length 4.
#
# Constraints:
# 1 <= s.length <= 100
# 	0 <= k <= s.length
# 	s contains only lowercase English letters.
#

class Solution(object):
    def getLengthOfOptimalCompression(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        dp = [[float('inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        def getLength(count):
            if count == 0:
                return 0
            elif count == 1:
                return 1
            elif count < 10:
                return 2
            elif count < 100:
                return 3
            else:
                return 4

        for i in range(1, n + 1):
            for j in range(0, k + 1):
                # Option 1: Delete s[i-1]
                if j > 0:
                    dp[i][j] = dp[i - 1][j - 1]

                # Option 2: Keep s[i-1]
                same = 0
                diff = 0
                for l in range(i, 0, -1):
                    if s[l - 1] == s[i - 1]:
                        same += 1
                    else:
                        diff += 1
                    if diff > j:
                        break
                    dp[i][j] = min(dp[i][j], dp[l - 1][j - diff] + getLength(same))

        return dp[n][k]