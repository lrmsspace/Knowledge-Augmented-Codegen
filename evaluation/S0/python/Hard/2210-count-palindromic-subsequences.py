# Source: https://leetcode.com/problems/count-palindromic-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.
#
# Note:
#
#
# 	A string is palindromic if it reads the same forward and backward.
# 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
#
# Example:
# Input: s = "103301"
# Output: 2
# Explanation: 
# There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301". 
# Two of them (both equal to "10301") are palindromic.
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of digits.
#

class Solution(object):
    def countPalindromes(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        
        # Precompute prefix and suffix counts
        prefix_count = [[0]*10 for _ in range(n)]
        suffix_count = [[0]*10 for _ in range(n)]
        
        for i in range(n):
            if i > 0:
                for d in range(10):
                    prefix_count[i][d] = prefix_count[i-1][d]
            prefix_count[i][int(s[i])] += 1
        
        for i in range(n-1, -1, -1):
            if i < n-1:
                for d in range(10):
                    suffix_count[i][d] = suffix_count[i+1][d]
            suffix_count[i][int(s[i])] += 1
        
        result = 0
        
        # Iterate over all possible centers of the palindrome
        for center in range(2, n-2):
            for d1 in range(10):
                for d2 in range(10):
                    count_left = prefix_count[center-1][d1]
                    count_right = suffix_count[center+1][d2]
                    result += count_left * count_right
                    result %= MOD
        
        return result