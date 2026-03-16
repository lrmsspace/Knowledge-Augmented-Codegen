# Source: https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary string s, partition the string into one or more substrings such that each substring is beautiful.
#
# A string is beautiful if:
#
#
# 	It doesn't contain leading zeros.
# 	It's the binary representation of a number that is a power of 5.
#
#
# Return the minimum number of substrings in such partition. If it is impossible to partition the string s into beautiful substrings, return -1.
#
# A substring is a contiguous sequence of characters in a string.
#
# Example:
# Input: s = "1011"
# Output: 2
# Explanation: We can paritition the given string into ["101", "1"].
# - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
# - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
# It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.
#
# Constraints:
# 1 <= s.length <= 15
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def minimumBeautifulSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        powers_of_five = set()
        power = 1
        while power <= 2**15:
            powers_of_five.add(bin(power)[2:])
            power *= 5

        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        for i in range(1, n + 1):
            for j in range(i):
                if s[j:i] in powers_of_five:
                    dp[i] = min(dp[i], dp[j] + 1)

        return dp[n] if dp[n] != float('inf') else -1