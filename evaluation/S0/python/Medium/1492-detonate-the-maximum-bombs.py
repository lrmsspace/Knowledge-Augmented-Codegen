# Source: https://leetcode.com/problems/detonate-the-maximum-bombs/   |   Difficulty: Medium
#
# Problem Description:
# You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in the shape of a circle with the center as the location of the bomb.
#
# The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.
#
# You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. These bombs will further detonate the bombs that lie in their ranges.
#
# Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.
#
# Example:
# Input: bombs = [[2,1,3],[6,1,4]]
# Output: 2
# Explanation:
# The above figure shows the positions and ranges of the 2 bombs.
# If we detonate the left bomb, the right bomb will not be affected.
# But if we detonate the right bomb, both bombs will be detonated.
# So the maximum bombs that can be detonated is max(1, 2) = 2.
#
# Constraints:
# 1 <= bombs.length <= 100
# 	bombs[i].length == 3
# 	1 <= xi, yi, ri <= 105
#

class Solution(object):
    def maximumDetonation(self, bombs):
        """
        :type bombs: List[List[int]]
        :rtype: int
        """
        n = len(bombs)
        graph = [[] for _ in range(n)]
        
        # Build the graph
        for i in range(n):
            x1, y1, r1 = bombs[i]
            for j in range(n):
                if i != j:
                    x2, y2, _ = bombs[j]
                    if (x2 - x1) ** 2 + (y2 - y1) ** 2 <= r1 ** 2:
                        graph[i].append(j)
        
        def bfs(start):
            visited = set()
            queue = [start]
            visited.add(start)
            while queue:
                node = queue.pop(0)
                for neighbor in graph[node]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
            return len(visited)
        
        max_detonated = 0
        for i in range(n):
            max_detonated = max(max_detonated, bfs(i))
        
        return max_detonated