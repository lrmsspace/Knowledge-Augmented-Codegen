# Source: https://leetcode.com/problems/robot-bounded-in-circle/   |   Difficulty: Medium
#
# Problem Description:
# On an infinite plane, a robot initially stands at (0, 0) and faces north. Note that:
#
#
# 	The north direction is the positive direction of the y-axis.
# 	The south direction is the negative direction of the y-axis.
# 	The east direction is the positive direction of the x-axis.
# 	The west direction is the negative direction of the x-axis.
#
#
# The robot can receive one of three instructions:
#
#
# 	"G": go straight 1 unit.
# 	"L": turn 90 degrees to the left (i.e., anti-clockwise direction).
# 	"R": turn 90 degrees to the right (i.e., clockwise direction).
#
#
# The robot performs the instructions given in order, and repeats them forever.
#
# Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.
#
# Example:
# Input: instructions = "GGLLGG"
# Output: true
# Explanation: The robot is initially at (0, 0) facing the north direction.
# "G": move one step. Position: (0, 1). Direction: North.
# "G": move one step. Position: (0, 2). Direction: North.
# "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: West.
# "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: South.
# "G": move one step. Position: (0, 1). Direction: South.
# "G": move one step. Position: (0, 0). Direction: South.
# Repeating the instructions, the robot goes into the cycle: (0, 0) --> (0, 1) --> (0, 2) --> (0, 1) --> (0, 0).
# Based on that, we return true.
#
# Constraints:
# 1 <= instructions.length <= 100
# 	instructions[i] is 'G', 'L' or, 'R'.
#

class Solution(object):
    def isRobotBounded(self, instructions):
        """
        :type instructions: str
        :rtype: bool
        """
        # Directions: North, East, South, West
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        x = y = 0  # Robot's position
        dir_idx = 0  # Index for directions, starting facing North

        for instruction in instructions:
            if instruction == 'G':
                x += directions[dir_idx][0]
                y += directions[dir_idx][1]
            elif instruction == 'L':
                dir_idx = (dir_idx - 1) % 4  # Turn left
            elif instruction == 'R':
                dir_idx = (dir_idx + 1) % 4  # Turn right

        # The robot is bounded in a circle if it returns to the origin
        # or it doesn't face North after one cycle of instructions
        return (x == 0 and y == 0) or (dir_idx != 0)