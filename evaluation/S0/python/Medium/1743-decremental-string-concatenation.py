# Source: https://leetcode.com/problems/decremental-string-concatenation/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array words containing n strings.
#
# Let's define a join operation join(x, y) between two strings x and y as concatenating them into xy. However, if the last character of x is equal to the first character of y, one of them is deleted.
#
# For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".
#
# You are to perform n - 1 join operations. Let str0 = words[0]. Starting from i = 1 up to i = n - 1, for the ith operation, you can do one of the following:
#
#
# 	Make stri = join(stri - 1, words[i])
# 	Make stri = join(words[i], stri - 1)
#
#
# Your task is to minimize the length of strn - 1.
#
# Return an integer denoting the minimum possible length of strn - 1.
#
# Example:
# Input: words = ["aa","ab","bc"]
# Output: 4
# Explanation: In this example, we can perform join operations in the following order to minimize the length of str2: 
# str0 = "aa"
# str1 = join(str0, "ab") = "aab"
# str2 = join(str1, "bc") = "aabc" 
# It can be shown that the minimum possible length of str2 is 4.
#
# Constraints:
# 1 <= words.length <= 1000
# 	1 <= words[i].length <= 50
# 	Each character in words[i] is an English lowercase letter
#

class Solution(object):
    def minimizeConcatenatedLength(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        n = len(words)
        dp = [[float('inf')] * 26 for _ in range(n)]
        
        for i in range(26):
            first_char = ord(words[0][0]) - ord('a')
            last_char = ord(words[0][-1]) - ord('a')
            dp[0][last_char] = len(words[0])
        
        for i in range(1, n):
            first_char = ord(words[i][0]) - ord('a')
            last_char = ord(words[i][-1]) - ord('a')
            length = len(words[i])
            
            for j in range(26):
                if dp[i-1][j] == float('inf'):
                    continue
                
                # Append words[i] to the end
                if j == first_char:
                    dp[i][last_char] = min(dp[i][last_char], dp[i-1][j] + length - 1)
                else:
                    dp[i][last_char] = min(dp[i][last_char], dp[i-1][j] + length)
                
                # Prepend words[i] to the beginning
                if last_char == j:
                    dp[i][first_char] = min(dp[i][first_char], dp[i-1][j] + length - 1)
                else:
                    dp[i][first_char] = min(dp[i][first_char], dp[i-1][j] + length)
        
        return min(dp[n-1])