# Source: https://leetcode.com/problems/minimum-sideway-jumps/   |   Difficulty: Medium
#
# Problem Description:
# There is a 3 lane road of length n that consists of n + 1 points labeled from 0 to n. A frog starts at point 0 in the second lane and wants to jump to point n. However, there could be obstacles along the way.
#
# You are given an array obstacles of length n + 1 where each obstacles[i] (ranging from 0 to 3) describes an obstacle on the lane obstacles[i] at point i. If obstacles[i] == 0, there are no obstacles at point i. There will be at most one obstacle in the 3 lanes at each point.
#
#
# 	For example, if obstacles[2] == 1, then there is an obstacle on lane 1 at point 2.
#
#
# The frog can only travel from point i to point i + 1 on the same lane if there is not an obstacle on the lane at point i + 1. To avoid obstacles, the frog can also perform a side jump to jump to another lane (even if they are not adjacent) at the same point if there is no obstacle on the new lane.
#
#
# 	For example, the frog can jump from lane 3 at point 3 to lane 1 at point 3.
#
#
# Return the minimum number of side jumps the frog needs to reach any lane at point n starting from lane 2 at point 0.
#
# Note: There will be no obstacles on points 0 and n.
#
# Example:
# Input: obstacles = [0,1,2,3,0]
# Output: 2 
# Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps (red arrows).
# Note that the frog can jump over obstacles only when making side jumps (as shown at point 2).
#
# Constraints:
# obstacles.length == n + 1
# 	1 <= n <= 5 * 105
# 	0 <= obstacles[i] <= 3
# 	obstacles[0] == obstacles[n] == 0
#

class Solution(object):
    def minSideJumps(self, obstacles):
        """
        :type obstacles: List[int]
        :rtype: int
        """
        n = len(obstacles)
        dp = [1, 0, 1]  # dp[i] 表示在当前点到达第 i 条车道所需的最小侧跳次数

        for i in range(1, n):
            if obstacles[i] != 0:
                dp[obstacles[i] - 1] = float('inf')  # 有障碍物的车道不可达

            min_jumps = min(dp)
            for j in range(3):
                if obstacles[i] != j + 1:
                    dp[j] = min(dp[j], min_jumps + 1)

        return min(dp)