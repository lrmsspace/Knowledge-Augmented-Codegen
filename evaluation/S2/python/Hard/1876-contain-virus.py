# Source: https://leetcode.com/problems/contain-virus/   |   Difficulty: Hard
#
# Problem Description:
# A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.
#
# The world is modeled as an m x n binary grid isInfected, where isInfected[i][j] == 0 represents uninfected cells, and isInfected[i][j] == 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.
#
# Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region (i.e., the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night). There will never be a tie.
#
# Return the number of walls used to quarantine all the infected regions. If the world will become fully infected, return the number of walls used.
#
# Example:
# Input: isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
# Output: 10
# Explanation: There are 2 contaminated regions.
# On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:
#
# On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
#
# Constraints:
# m == isInfected.length
# 	n == isInfected[i].length
# 	1 <= m, n <= 50
# 	isInfected[i][j] is either 0 or 1.
# 	There is always a contiguous viral region throughout the described process that will infect strictly more uncontaminated squares in the next round.
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
    def containVirus(self, isInfected):
        """
        :type isInfected: List[List[int]]
        :rtype: int
        """
        from collections import deque
        
        m, n = len(isInfected), len(isInfected[0])
        total_walls = 0
        
        while True:
            visited = [[False] * n for _ in range(m)]
            regions = []
            frontiers = []
            walls_needed = []
            
            # Step 1: Identify all infected regions and their frontiers
            for i in range(m):
                for j in range(n):
                    if isInfected[i][j] == 1 and not visited[i][j]:
                        region = []
                        frontier = set()
                        walls = 0
                        queue = deque([(i, j)])
                        visited[i][j] = True
                        
                        while queue:
                            x, y = queue.popleft()
                            region.append((x, y))
                            
                            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                                nx, ny = x + dx, y + dy
                                if 0 <= nx < m and 0 <= ny < n:
                                    if isInfected[nx][ny] == 0:
                                        frontier.add((nx, ny))
                                        walls += 1
                                    elif isInfected[nx][ny] == 1 and not visited[nx][ny]:
                                        visited[nx][ny] = True
                                        queue.append((nx, ny))
                        
                        regions.append(region)
                        frontiers.append(frontier)
                        walls_needed.append(walls)
            
            if not regions:
                break
            
            # Step 2: Find the region that threatens the most uninfected cells
            max_threat_index = max(range(len(frontiers)), key=lambda i: len(frontiers[i]))
            
            # Step 3: Build walls around the most threatening region
            total_walls += walls_needed[max_threat_index]
            for x, y in regions[max_threat_index]:
                isInfected[x][y] = -1  # Mark as contained
            
            # Step 4: Spread the virus from other regions
            for i in range(len(regions)):
                if i != max_threat_index:
                    for x, y in frontiers[i]:
                        isInfected[x][y] = 1
        
        return total_walls