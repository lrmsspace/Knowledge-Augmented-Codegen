# Source: https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:
#
#
# 	'S': Starting position of the student
# 	'L': Litter that must be collected (once collected, the cell becomes empty)
# 	'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
# 	'X': Obstacle the student cannot pass through
# 	'.': Empty space
#
#
# You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.
#
# Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.
#
# Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.
#
# Example:
# Input: classroom = ["S.", "XL"], energy = 2
#
# Output: 2
#
# Explanation:
#
#
# 	The student starts at cell (0, 0) with 2 units of energy.
# 	Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
# 	A valid sequence of moves to collect all litter is as follows:
# 	
# 		Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
# 		Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
# 	
# 	
# 	The student collects all the litter using 2 moves. Thus, the output is 2.
#
# Constraints:
# 1 <= m == classroom.length <= 20
# 	1 <= n == classroom[i].length <= 20
# 	classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
# 	1 <= energy <= 50
# 	There is exactly one 'S' in the grid.
# 	There are at most 10 'L' cells in the grid.
#

class Solution(object):
    def minMoves(self, classroom, energy):
        """
        :type classroom: List[str]
        :type energy: int
        :rtype: int
        """
        from collections import deque
        m, n = len(classroom), len(classroom[0])
        litter_positions = []
        start = None
        
        for i in range(m):
            for j in range(n):
                if classroom[i][j] == 'S':
                    start = (i, j)
                elif classroom[i][j] == 'L':
                    litter_positions.append((i, j))
        
        litter_count = len(litter_positions)
        all_collected_mask = (1 << litter_count) - 1
        
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        def bfs(start_pos):
            dist = [[[-1] * (energy + 1) for _ in range(n)] for _ in range(m)]
            queue = deque()
            x, y = start_pos
            dist[x][y][energy] = 0
            queue.append((x, y, energy))
            
            while queue:
                x, y, e = queue.popleft()
                
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and classroom[nx][ny] != 'X':
                        ne = e - 1
                        if ne < 0:
                            continue
                        if classroom[nx][ny] == 'R':
                            ne = energy
                        if dist[nx][ny][ne] == -1:
                            dist[nx][ny][ne] = dist[x][y][e] + 1
                            queue.append((nx, ny, ne))
            return dist
        
        dists_from_start = bfs(start)
        dists_from_litter = [bfs(pos) for pos in litter_positions]
        
        dp = [[float('inf')] * (1 << litter_count) for _ in range(litter_count)]
        
        for i in range(litter_count):
            lx, ly = litter_positions[i]
            for e in range(energy + 1):
                if dists_from_start[lx][ly][e] != -1:
                    dp[i][1 << i] = min(dp[i][1 << i], dists_from_start[lx][ly][e])
        
        for mask in range(1 << litter_count):
            for u in range(litter_count