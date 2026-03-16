# Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/   |   Difficulty: Medium
#
# Problem Description:
# There is a dungeon with n x m rooms arranged as a grid.
#
# You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds after which the room opens and can be moved to. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes exactly one second.
#
# Return the minimum time to reach the room (n - 1, m - 1).
#
# Two rooms are adjacent if they share a common wall, either horizontally or vertically.
#
# Example:
# Input: moveTime = [[0,4],[4,4]]
#
# Output: 6
#
# Explanation:
#
# The minimum time required is 6 seconds.
#
#
# 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
# 	At time t == 5, move from room (1, 0) to room (1, 1) in one second.
#
# Constraints:
# 2 <= n == moveTime.length <= 50
# 	2 <= m == moveTime[i].length <= 50
# 	0 <= moveTime[i][j] <= 109
#

class Solution(object):
    def minTimeToReach(self, moveTime):
        """
        :type moveTime: List[List[int]]
        :rtype: int
        """
        import heapq

        n, m = len(moveTime), len(moveTime[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        min_heap = [(0, 0, 0)]  # (time, x, y)
        visited = set()

        while min_heap:
            time, x, y = heapq.heappop(min_heap)

            if (x, y) in visited:
                continue
            visited.add((x, y))

            if x == n - 1 and y == m - 1:
                return time

            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < n and 0 <= ny < m:
                    arrival_time = time + 1
                    if arrival_time < moveTime[nx][ny]:
                        wait_time = moveTime[nx][ny] - arrival_time
                        if wait_time % 2 == 0:
                            arrival_time += wait_time
                        else:
                            arrival_time += wait_time + 1
                    heapq.heappush(min_heap, (arrival_time, nx, ny))

        return -1