# Source: https://leetcode.com/problems/escape-a-large-maze/   |   Difficulty: Hard
#
# Problem Description:
# There is a 1 million by 1 million grid on an XY-plane, and the coordinates of each grid square are (x, y).
#
# We start at the source = [sx, sy] square and want to reach the target = [tx, ty] square. There is also an array of blocked squares, where each blocked[i] = [xi, yi] represents a blocked square with coordinates (xi, yi).
#
# Each move, we can walk one square north, east, south, or west if the square is not in the array of blocked squares. We are also not allowed to walk outside of the grid.
#
# Return true if and only if it is possible to reach the target square from the source square through a sequence of valid moves.
#
# Example:
# Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
# Output: false
# Explanation: The target square is inaccessible starting from the source square because we cannot move.
# We cannot move north or east because those squares are blocked.
# We cannot move south or west because we cannot go outside of the grid.
#
# Constraints:
# 0 <= blocked.length <= 200
# 	blocked[i].length == 2
# 	0 <= xi, yi < 106
# 	source.length == target.length == 2
# 	0 <= sx, sy, tx, ty < 106
# 	source != target
# 	It is guaranteed that source and target are not blocked.
#

class Solution(object):
    def isEscapePossible(self, blocked, source, target):
        """
        :type blocked: List[List[int]]
        :type source: List[int]
        :type target: List[int]
        :rtype: bool
        """
        BLOCKED = -1
        VALID = 0
        FOUND = 1
        MAX_STEPS = len(blocked) * (len(blocked) - 1) // 2

        def check(start, finish):
            visited = set()
            stack = [(start[0], start[1])]
            visited.add((start[0], start[1]))
            steps = 0

            while stack:
                x, y = stack.pop()
                if [x, y] == finish:
                    return FOUND
                for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < 10**6 and 0 <= ny < 10**6 and (nx, ny) not in blocked_set and (nx, ny) not in visited:
                        visited.add((nx, ny))
                        stack.append((nx, ny))
                steps += 1
                if steps >= MAX_STEPS:
                    return VALID
            return BLOCKED

        blocked_set = set(map(tuple, blocked))
        result_from_source = check(source, target)
        if result_from_source == FOUND:
            return True
        elif result_from_source == BLOCKED:
            return False
        else:
            result_from_target = check(target, source)
            return result_from_target != BLOCKED