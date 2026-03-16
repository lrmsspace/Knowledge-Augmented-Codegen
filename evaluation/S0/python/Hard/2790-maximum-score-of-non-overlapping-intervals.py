# Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.
#
# Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.
#
# Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
#
# Example:
# Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
#
# Output: [2,3]
#
# Explanation:
#
# You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
#
# Constraints:
# 1 <= intevals.length <= 5 * 104
# 	intervals[i].length == 3
# 	intervals[i] = [li, ri, weighti]
# 	1 <= li <= ri <= 109
# 	1 <= weighti <= 109
#

class Solution(object):
    def maximumWeight(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: List[int]
        """
        from bisect import bisect_right

        intervals = sorted(
            [(start, end, weight, i) for i, (start, end, weight) in enumerate(intervals)]
        )
        n = len(intervals)
        dp = [[(0, []) for _ in range(5)] for _ in range(n + 1)]

        starts = [intervals[i][0] for i in range(n)]

        for i in range(n - 1, -1, -1):
            start, end, weight, idx = intervals[i]
            next_index = bisect_right(starts, end)

            for k in range(1, 5):
                not_take = dp[i + 1][k]
                take = (weight + dp[next_index][k - 1][0],
                        [idx] + dp[next_index][k - 1][1])

                if take[0] > not_take[0] or (take[0] == not_take[0] and take[1] < not_take[1]):
                    dp[i][k] = take
                else:
                    dp[i][k] = not_take

        return dp[0][4][1]  