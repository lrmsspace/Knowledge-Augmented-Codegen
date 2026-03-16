# Source: https://leetcode.com/problems/maximum-total-damage-with-spell-casting/   |   Difficulty: Medium
#
# Problem Description:
# A magician has various spells.
#
# You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same damage value.
#
# It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.
#
# Each spell can be cast only once.
#
# Return the maximum possible total damage that a magician can cast.
#
# Example:
# Input: power = [1,1,3,4]
#
# Output: 6
#
# Explanation:
#
# The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.
#
# Constraints:
# 1 <= power.length <= 105
# 	1 <= power[i] <= 109
#

class Solution(object):
    def maximumTotalDamage(self, power):
        """
        :type power: List[int]
        :rtype: int
        """
        from collections import Counter

        count = Counter(power)
        unique_powers = sorted(count.keys())

        n = len(unique_powers)
        dp = [0] * (n + 1)

        for i in range(1, n + 1):
            current_power = unique_powers[i - 1]
            current_damage = current_power * count[current_power]

            if i == 1:
                dp[i] = current_damage
            else:
                if unique_powers[i - 2] + 2 <= current_power:
                    dp[i] = dp[i - 1] + current_damage
                else:
                    dp[i] = max(dp[i - 1], dp[i - 2] + current_damage)

        return dp[n]