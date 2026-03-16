# Source: https://leetcode.com/problems/minimum-time-to-transport-all-individuals/   |   Difficulty: Hard
#
# Problem Description:
# You are given n individuals at a base camp who need to cross a river to reach a destination using a single boat. The boat can carry at most k people at a time. The trip is affected by environmental conditions that vary cyclically over m stages.
#
# Each stage j has a speed multiplier mul[j]:
#
#
# 	If mul[j] > 1, the trip slows down.
# 	If mul[j] < 1, the trip speeds up.
#
#
# Each individual i has a rowing strength represented by time[i], the time (in minutes) it takes them to cross alone in neutral conditions.
#
# Rules:
#
#
# 	A group g departing at stage j takes time equal to the maximum time[i] among its members, multiplied by mul[j] minutes to reach the destination.
# 	After the group crosses the river in time d, the stage advances by floor(d) % m steps.
# 	If individuals are left behind, one person must return with the boat. Let r be the index of the returning person, the return takes time[r] × mul[current_stage], defined as return_time, and the stage advances by floor(return_time) % m.
#
#
# Return the minimum total time required to transport all individuals. If it is not possible to transport all individuals to the destination, return -1.
#
# Example:
# Input: n = 1, k = 1, m = 2, time = [5], mul = [1.0,1.3]
#
# Output: 5.00000
#
# Explanation:
#
#
# 	Individual 0 departs from stage 0, so crossing time = 5 × 1.00 = 5.00 minutes.
# 	All team members are now at the destination. Thus, the total time taken is 5.00 minutes.
#
# Constraints:
# 1 <= n == time.length <= 12
# 	1 <= k <= 5
# 	1 <= m <= 5
# 	1 <= time[i] <= 100
# 	m == mul.length
# 	0.5 <= mul[i] <= 2.0
#

class Solution(object):
    def minTime(self, n, k, m, time, mul):
        """
        :type n: int
        :type k: int
        :type m: int
        :type time: List[int]
        :type mul: List[float]
        :rtype: float
        """
        from itertools import combinations
        from math import floor

        ALL = (1 << n) - 1
        dp = [[float('inf')] * m for _ in range(1 << n)]
        dp[0][0] = 0

        for mask in range(1 << n):
            for stage in range(m):
                if dp[mask][stage] == float('inf'):
                    continue

                remaining = [i for i in range(n) if not (mask & (1 << i))]
                for group_size in range(1, min(k, len(remaining)) + 1):
                    for group in combinations(remaining, group_size):
                        new_mask = mask
                        max_time = 0
                        for person in group:
                            new_mask |= (1 << person)
                            max_time = max(max_time, time[person])

                        cross_time = max_time * mul[stage]
                        new_stage = (stage + floor(cross_time)) % m
                        total_time = dp[mask][stage] + cross_time

                        if new_mask != ALL:
                            min_return_time = float('inf')
                            for return_person in group:
                                return_time = time[return_person] * mul[new_stage]
                                min_return_time = min(min_return_time, return_time)

                            total_time += min_return_time
                            new_stage = (new_stage + floor(min_return_time)) % m

                        dp[new_mask][new_stage] = min(dp[new_mask][new_stage], total_time)

        result = min(dp[ALL])
        return result if result != float('inf') else -1