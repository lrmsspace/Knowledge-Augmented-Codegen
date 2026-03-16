# Source: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.
#
# Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].
#
# Return the maximum number of subarrays possible after removing exactly one conflicting pair.
#
# Example:
# Input: n = 4, conflictingPairs = [[2,3],[1,4]]
#
# Output: 9
#
# Explanation:
#
#
# 	Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
# 	There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
# 	The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= conflictingPairs.length <= 2 * n
# 	conflictingPairs[i].length == 2
# 	1 <= conflictingPairs[i][j] <= n
# 	conflictingPairs[i][0] != conflictingPairs[i][1]
#

class Solution(object):
    def maxSubarrays(self, n, conflictingPairs):
        """
        :type n: int
        :type conflictingPairs: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        conflict_map = defaultdict(list)
        for a, b in conflictingPairs:
            conflict_map[a].append(b)
            conflict_map[b].append(a)

        total_subarrays = n * (n + 1) // 2
        left, res = 0, 0
        last_conflict = {}

        for right in range(1, n + 1):
            if right in conflict_map:
                for c in conflict_map[right]:
                    if c in last_conflict:
                        left = max(left, last_conflict[c] + 1)
            last_conflict[right] = right
            res += right - left

        max_removal_gain = 0
        for a, b in conflictingPairs:
            removal_gain = (last_conflict.get(a, 0) - last_conflict.get(b, 0)) * (n - max(a, b) + 1)
            max_removal_gain = max(max_removal_gain, removal_gain)

        return total_subarrays - (res - max_removal_gain)