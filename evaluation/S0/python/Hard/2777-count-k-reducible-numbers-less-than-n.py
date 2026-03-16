# Source: https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary string s representing a number n in its binary form.
#
# You are also given an integer k.
#
# An integer x is called k-reducible if performing the following operation at most k times reduces it to 1:
#
#
# 	Replace x with the count of set bits in its binary representation.
#
#
# For example, the binary representation of 6 is "110". Applying the operation once reduces it to 2 (since "110" has two set bits). Applying the operation again to 2 (binary "10") reduces it to 1 (since "10" has one set bit).
#
# Return an integer denoting the number of positive integers less than n that are k-reducible.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: s = "111", k = 1
#
# Output: 3
#
# Explanation: 
#
# n = 7. The 1-reducible integers less than 7 are 1, 2, and 4.
#
# Constraints:
# 1 <= s.length <= 800
# 	s has no leading zeros.
# 	s consists only of the characters '0' and '1'.
# 	1 <= k <= 5
#

class Solution(object):
    def countKReducibleNumbers(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # Precompute the number of steps to reduce to 1 for numbers up to 800
        max_bits = 800
        steps_to_one = [0] * (max_bits + 1)
        for i in range(2, max_bits + 1):
            steps_to_one[i] = steps_to_one[bin(i).count('1')] + 1
        
        # Count how many numbers have exactly j steps to reduce to 1
        count_steps = [0] * (max_bits + 1)
        for i in range(1, max_bits + 1):
            count_steps[steps_to_one[i]] += 1
        
        # Function to count numbers with exactly j set bits less than binary string s
        def count_with_set_bits(s, j):
            n = len(s)
            dp = [[0] * (j + 1) for _ in range(n + 1)]
            dp[0][0] = 1
            
            for i in range(1, n + 1):
                bit = int(s[i - 1])
                for k in range(j + 1):
                    dp[i][k] += dp[i - 1][k]
                    if bit == 1 and k > 0:
                        dp[i][k] += dp[i - 1][k - 1]
                    dp[i][k] %= MOD
            
            return dp[n][j]
        
        result = 0
        for j in range(1, max_bits + 1):
            if steps_to_one[j] == k:
                result += count_with_set_bits(s, j)
                result %= MOD
        
        # Exclude the case when the number is n itself
        if steps_to_one[bin(int(s, 2)).count('1')] == k:
            result = (result - 1 + MOD) % MOD
        
        return result