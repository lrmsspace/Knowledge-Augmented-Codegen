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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

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
        from math import floor
        from functools import lru_cache

        @lru_cache(None)
        def dfs(state, stage):
            if state == 0:
                return 0.0
            res = float('inf')
            for group in self.get_groups(state, k):
                max_time = max(time[i] for i in group)
                trip_time = max_time * mul[stage]
                next_stage = (stage + floor(trip_time)) % m
                next_state = state & ~sum(1 << i for i in group)
                return_time = 0.0
                if next_state != 0:
                    return_person = min((time[i], i) for i in group)[1]
                    return_time = time[return_person] * mul[next_stage]
                    next_stage = (next_stage + floor(return_time)) % m
                    next_state |= 1 << return_person
                res = min(res, trip_time + return_time + dfs(next_state, next_stage))
            return res

        result = dfs((1 << n) - 1, 0)
        return result if result != float('inf') else -1