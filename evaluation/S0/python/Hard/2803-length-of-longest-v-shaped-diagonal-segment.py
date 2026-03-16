# Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
#
# A V-shaped diagonal segment is defined as:
#
#
# 	The segment starts with 1.
# 	The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
# 	The segment:
# 	
# 		Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
# 		Continues the sequence in the same diagonal direction.
# 		Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.
# 	
# 	
#
#
# Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
#
# Example:
# Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
#
# Output: 5
#
# Explanation:
#
#
#
# The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).
#
# Constraints:
# n == grid.length
# 	m == grid[i].length
# 	1 <= n, m <= 500
# 	grid[i][j] is either 0, 1 or 2.
#

class Solution(object):
    def lenOfVDiagonal(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n, m = len(grid), len(grid[0])
        directions = [(-1, -1), (-1, 1), (1, -1), (1, 1)]
        seq = [1, 2, 0, 2]

        def in_bounds(x, y):
            return 0 <= x < n and 0 <= y < m

        max_length = 0

        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    for d in directions:
                        length = 1
                        x, y = i + d[0], j + d[1]
                        seq_index = 1
                        turned = False

                        while in_bounds(x, y):
                            if grid[x][y] == seq[seq_index]:
                                length += 1
                                seq_index = (seq_index + 1) % 4
                                x += d[0]
                                y += d[1]
                            elif not turned:
                                new_directions = [dir for dir in directions if dir != d]
                                turned = True
                                turned_successfully = False

                                for nd in new_directions:
                                    nx, ny = x + nd[0], y + nd[1]
                                    if in_bounds(nx, ny) and grid[nx][ny] == seq[seq_index]:
                                        d = nd
                                        x, y = nx, ny
                                        length += 1
                                        seq_index = (seq_index + 1) % 4
                                        turned_successfully = True
                                        break

                                if not turned_successfully:
                                    break
                            else:
                                break

                        max_length = max(max_length, length)

        return max_length