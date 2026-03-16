# Source: https://leetcode.com/problems/path-crossing/   |   Difficulty: Easy
#
# Problem Description:
# Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.
#
# Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.
#
# Example:
# Input: path = "NES"
# Output: false 
# Explanation: Notice that the path doesn't cross any point more than once.
#
# Constraints:
# 1 <= path.length <= 104
# 	path[i] is either 'N', 'S', 'E', or 'W'.
#

class Solution(object):
    def isPathCrossing(self, path):
        """
        :type path: str
        :rtype: bool
        """
        visited = set()
        x, y = 0, 0
        visited.add((x, y))
        
        for direction in path:
            if direction == 'N':
                y += 1
            elif direction == 'S':
                y -= 1
            elif direction == 'E':
                x += 1
            elif direction == 'W':
                x -= 1
            
            if (x, y) in visited:
                return True
            visited.add((x, y))
        
        return False