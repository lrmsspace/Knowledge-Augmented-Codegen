# Source: https://leetcode.com/problems/walking-robot-simulation/   |   Difficulty: Medium
#
# Problem Description:
# A robot on an infinite XY-plane starts at point (0, 0) facing north. The robot receives an array of integers commands, which represents a sequence of moves that it needs to execute. There are only three possible types of instructions the robot can receive:
#
#
# 	-2: Turn left 90 degrees.
# 	-1: Turn right 90 degrees.
# 	1 <= k <= 9: Move forward k units, one unit at a time.
#
#
# Some of the grid squares are obstacles. The ith obstacle is at grid point obstacles[i] = (xi, yi). If the robot runs into an obstacle, it will stay in its current location (on the block adjacent to the obstacle) and move onto the next command.
#
# Return the maximum squared Euclidean distance that the robot reaches at any point in its path (i.e. if the distance is 5, return 25).
#
# Note:
#
#
# 	There can be an obstacle at (0, 0). If this happens, the robot will ignore the obstacle until it has moved off the origin. However, it will be unable to return to (0, 0) due to the obstacle.
# 	North means +Y direction.
# 	East means +X direction.
# 	South means -Y direction.
# 	West means -X direction.
#
# Example:
# Input: commands = [4,-1,3], obstacles = []
#
# Output: 25
#
# Explanation: 
#
# The robot starts at (0, 0):
#
#
# 	Move north 4 units to (0, 4).
# 	Turn right.
# 	Move east 3 units to (3, 4).
#
#
# The furthest point the robot ever gets from the origin is (3, 4), which squared is 32 + 42 = 25 units away.
#
# Constraints:
# 1 <= commands.length <= 104
# 	commands[i] is either -2, -1, or an integer in the range [1, 9].
# 	0 <= obstacles.length <= 104
# 	-3 * 104 <= xi, yi <= 3 * 104
# 	The answer is guaranteed to be less than 231.
#

class Solution(object):
    def robotSim(self, commands, obstacles):
        """
        :type commands: List[int]
        :type obstacles: List[List[int]]
        :rtype: int
        """
        # Directions: North, East, South, West
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        x = y = di = 0  # Starting position and direction index
        obstacle_set = set(map(tuple, obstacles))  # Convert list of obstacles to a set for O(1) lookups
        max_distance_sq = 0

        for command in commands:
            if command == -2:  # Turn left
                di = (di - 1) % 4
            elif command == -1:  # Turn right
                di = (di + 1) % 4
            else:  # Move forward command units
                for _ in range(command):
                    next_x = x + directions[di][0]
                    next_y = y + directions[di][1]
                    if (next_x, next_y) not in obstacle_set:
                        x, y = next_x, next_y
                        max_distance_sq = max(max_distance_sq, x*x + y*y)
                    else:
                        break  # Stop moving if there's an obstacle

        return max_distance_sq