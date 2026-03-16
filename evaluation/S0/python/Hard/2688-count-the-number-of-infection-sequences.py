# Source: https://leetcode.com/problems/count-the-number-of-infection-sequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and an array sick sorted in increasing order, representing positions of infected people in a line of n people.
#
# At each step, one uninfected person adjacent to an infected person gets infected. This process continues until everyone is infected.
#
# An infection sequence is the order in which uninfected people become infected, excluding those initially infected.
#
# Return the number of different infection sequences possible, modulo 109+7.
#
# Example:
# Input: n = 5, sick = [0,4]
#
# Output: 4
#
# Explanation:
#
# There is a total of 6 different sequences overall.
#
#
# 	Valid infection sequences are [1,2,3], [1,3,2], [3,2,1] and [3,1,2].
# 	[2,3,1] and [2,1,3] are not valid infection sequences because the person at index 2 cannot be infected at the first step.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= sick.length <= n - 1
# 	0 <= sick[i] <= n - 1
# 	sick is sorted in increasing order.
#

class Solution(object):
    def numberOfSequence(self, n, sick):
        """
        :type n: int
        :type sick: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7

        # Precompute factorials and inverse factorials for combinations
        fact = [1] * (n + 1)
        inv_fact = [1] * (n + 1)
        for i in range(2, n + 1):
            fact[i] = fact[i - 1] * i % MOD
        inv_fact[n] = pow(fact[n], MOD - 2, MOD)
        for i in range(n - 1, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD

        def comb(a, b):
            if b > a or b < 0:
                return 0
            return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD

        segments = []
        prev = -1
        for s in sick:
            if prev + 1 < s:
                segments.append(s - prev - 1)
            prev = s
        if prev < n - 1:
            segments.append(n - prev - 1)

        total_ways = 1
        total_people = 0

        for i, seg in enumerate(segments):
            if i != 0 and i != len(segments) - 1:
                ways = comb(total_people + seg, seg) * pow(2, seg - 1, MOD) % MOD
            else:
                ways = comb(total_people + seg, seg) % MOD

            total_ways = total_ways * ways % MOD
            total_people += seg

        return total_ways