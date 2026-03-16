# Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/   |   Difficulty: Medium
#
# Problem Description:
# There is a dungeon with n x m rooms arranged as a grid.
#
# You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.
#
# Return the minimum time to reach the room (n - 1, m - 1).
#
# Two rooms are adjacent if they share a common wall, either horizontally or vertically.
#
# Example:
# Input: moveTime = [[0,4],[4,4]]
#
# Output: 7
#
# Explanation:
#
# The minimum time required is 7 seconds.
#
#
# 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
# 	At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.
#
# Constraints:
# 2 <= n == moveTime.length <= 750
# 	2 <= m == moveTime[i].length <= 750
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
                    next_time = time + 1 if (time % 2 == 0) else time + 2
                    if next_time < moveTime[nx][ny]:
                        wait_time = moveTime[nx][ny] - next_time
                        if wait_time % 2 == 1:
                            wait_time += 1
                        next_time += wait_time
                    heapq.heappush(min_heap, (next_time, nx, ny))

        return -1