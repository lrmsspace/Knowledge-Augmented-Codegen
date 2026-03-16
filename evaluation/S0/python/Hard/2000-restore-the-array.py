# Source: https://leetcode.com/problems/restore-the-array/   |   Difficulty: Hard
#
# Problem Description:
# A program was supposed to print an array of integers. The program forgot to print whitespaces and the array is printed as a string of digits s and all we know is that all integers in the array were in the range [1, k] and there are no leading zeros in the array.
#
# Given the string s and the integer k, return the number of the possible arrays that can be printed as s using the mentioned program. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: s = "1000", k = 10000
# Output: 1
# Explanation: The only possible array is [1000]
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of only digits and does not contain leading zeros.
# 	1 <= k <= 109
#

class Solution(object):
    def numberOfArrays(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        mod = 10**9 + 7
        dp = [0] * (n + 1)
        dp[n] = 1  # Base case: there's one way to decode an empty string

        for i in range(n - 1, -1, -1):
            if s[i] == '0':
                continue  # No valid number starts with '0'
            num = 0
            for j in range(i, n):
                num = num * 10 + int(s[j])
                if num > k:
                    break
                dp[i] = (dp[i] + dp[j + 1]) % mod

        return dp[0]