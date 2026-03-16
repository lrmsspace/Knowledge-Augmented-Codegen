# Source: https://leetcode.com/problems/avoid-flood-in-the-city/   |   Difficulty: Medium
#
# Problem Description:
# Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.
#
# Given an integer array rains where:
#
#
# 	rains[i] > 0 means there will be rains over the rains[i] lake.
# 	rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
#
#
# Return an array ans where:
#
#
# 	ans.length == rains.length
# 	ans[i] == -1 if rains[i] > 0.
# 	ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
#
#
# If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.
#
# Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes.
#
# Example:
# Input: rains = [1,2,3,4]
# Output: [-1,-1,-1,-1]
# Explanation: After the first day full lakes are [1]
# After the second day full lakes are [1,2]
# After the third day full lakes are [1,2,3]
# After the fourth day full lakes are [1,2,3,4]
# There's no day to dry any lake and there is no flood in any lake.
#
# Constraints:
# 1 <= rains.length <= 105
# 	0 <= rains[i] <= 109
#

class Solution(object):
    def avoidFlood(self, rains):
        """
        :type rains: List[int]
        :rtype: List[int]
        """
        import bisect

        n = len(rains)
        ans = [-1] * n
        full_lakes = {}
        dry_days = []

        for i in range(n):
            if rains[i] == 0:
                dry_days.append(i)
                ans[i] = 1  # Default value, will be updated if we dry a lake
            else:
                lake = rains[i]
                if lake in full_lakes:
                    last_full_day = full_lakes[lake]
                    idx = bisect.bisect_right(dry_days, last_full_day)
                    if idx == len(dry_days):
                        return []  # No available dry day to prevent flood
                    dry_day = dry_days[idx]
                    ans[dry_day] = lake  # Dry this lake on the chosen dry day
                    dry_days.pop(idx)  # Remove this dry day from available days
                full_lakes[lake] = i  # Mark this lake as full on day i

        return ans