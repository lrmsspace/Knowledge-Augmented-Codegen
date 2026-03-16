# Source: https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer hoursBefore, the number of hours you have to travel to your meeting. To arrive at your meeting, you have to travel through n roads. The road lengths are given as an integer array dist of length n, where dist[i] describes the length of the ith road in kilometers. In addition, you are given an integer speed, which is the speed (in km/h) you will travel at.
#
# After you travel road i, you must rest and wait for the next integer hour before you can begin traveling on the next road. Note that you do not have to rest after traveling the last road because you are already at the meeting.
#
#
# 	For example, if traveling a road takes 1.4 hours, you must wait until the 2 hour mark before traveling the next road. If traveling a road takes exactly 2 hours, you do not need to wait.
#
#
# However, you are allowed to skip some rests to be able to arrive on time, meaning you do not need to wait for the next integer hour. Note that this means you may finish traveling future roads at different hour marks.
#
#
# 	For example, suppose traveling the first road takes 1.4 hours and traveling the second road takes 0.6 hours. Skipping the rest after the first road will mean you finish traveling the second road right at the 2 hour mark, letting you start traveling the third road immediately.
#
#
# Return the minimum number of skips required to arrive at the meeting on time, or -1 if it is impossible.
#
# Example:
# Input: dist = [1,3,2], speed = 4, hoursBefore = 2
# Output: 1
# Explanation:
# Without skipping any rests, you will arrive in (1/4 + 3/4) + (3/4 + 1/4) + (2/4) = 2.5 hours.
# You can skip the first rest to arrive in ((1/4 + 0) + (3/4 + 0)) + (2/4) = 1.5 hours.
# Note that the second rest is shortened because you finish traveling the second road at an integer hour due to skipping the first rest.
#
# Constraints:
# n == dist.length
# 	1 <= n <= 1000
# 	1 <= dist[i] <= 105
# 	1 <= speed <= 106
# 	1 <= hoursBefore <= 107
#

class Solution(object):
    def minSkips(self, dist, speed, hoursBefore):
        """
        :type dist: List[int]
        :type speed: int
        :type hoursBefore: int
        :rtype: int
        """
        n = len(dist)
        dp = [[float('inf')] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            d = dist[i - 1]
            for j in range(i + 1):
                # Not skipping the rest after the i-th road
                if j < i:
                    dp[i][j] = min(dp[i][j], ((dp[i - 1][j] + d + speed - 1) // speed) * speed)
                # Skipping the rest after the i-th road
                if j > 0:
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + d)

        for j in range(n + 1):
            if dp[n][j] <= hoursBefore * speed:
                return j
        return -1