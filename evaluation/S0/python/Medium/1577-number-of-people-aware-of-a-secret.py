# Source: https://leetcode.com/problems/number-of-people-aware-of-a-secret/   |   Difficulty: Medium
#
# Problem Description:
# On day 1, one person discovers a secret.
#
# You are given an integer delay, which means that each person will share the secret with a new person every day, starting from delay days after discovering the secret. You are also given an integer forget, which means that each person will forget the secret forget days after discovering it. A person cannot share the secret on the same day they forgot it, or on any day afterwards.
#
# Given an integer n, return the number of people who know the secret at the end of day n. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 6, delay = 2, forget = 4
# Output: 5
# Explanation:
# Day 1: Suppose the first person is named A. (1 person)
# Day 2: A is the only person who knows the secret. (1 person)
# Day 3: A shares the secret with a new person, B. (2 people)
# Day 4: A shares the secret with a new person, C. (3 people)
# Day 5: A forgets the secret, and B shares the secret with a new person, D. (3 people)
# Day 6: B shares the secret with E, and C shares the secret with F. (5 people)
#
# Constraints:
# 2 <= n <= 1000
# 	1 <= delay < forget <= n
#

class Solution(object):
    def peopleAwareOfSecret(self, n, delay, forget):
        """
        :type n: int
        :type delay: int
        :type forget: int
        :rtype: int
        """
        MOD = 10**9 + 7
        dp = [0] * (n + 1)
        dp[1] = 1  # On day 1, one person knows the secret

        for day in range(2, n + 1):
            # People who can share the secret today
            for j in range(max(1, day - forget + 1), day - delay + 1):
                dp[day] = (dp[day] + dp[j]) % MOD

        # Sum up the people who still remember the secret on day n
        result = sum(dp[max(1, n - forget + 1):n + 1]) % MOD
        return result