# Source: https://leetcode.com/problems/tallest-billboard/   |   Difficulty: Hard
#
# Problem Description:
# You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.
#
# You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
#
# Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.
#
# Example:
# Input: rods = [1,2,3,6]
# Output: 6
# Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
#
# Constraints:
# 1 <= rods.length <= 20
# 	1 <= rods[i] <= 1000
# 	sum(rods[i]) <= 5000
#

class Solution(object):
    def tallestBillboard(self, rods):
        """
        :type rods: List[int]
        :rtype: int
        """
        dp = {0: 0}
        for rod in rods:
            cur = dp.copy()
            for diff, y in cur.items():
                x = y + diff
                dp[diff + rod] = max(dp.get(diff + rod, 0), y)
                dp[abs(diff - rod)] = max(dp.get(abs(diff - rod), 0), x if diff >= rod else y + rod - diff)
        return dp[0]