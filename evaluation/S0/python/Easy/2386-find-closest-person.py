# Source: https://leetcode.com/problems/find-closest-person/   |   Difficulty: Easy
#
# Problem Description:
# You are given three integers x, y, and z, representing the positions of three people on a number line:
#
#
# 	x is the position of Person 1.
# 	y is the position of Person 2.
# 	z is the position of Person 3, who does not move.
#
#
# Both Person 1 and Person 2 move toward Person 3 at the same speed.
#
# Determine which person reaches Person 3 first:
#
#
# 	Return 1 if Person 1 arrives first.
# 	Return 2 if Person 2 arrives first.
# 	Return 0 if both arrive at the same time.
#
#
# Return the result accordingly.
#
# Example:
# Input: x = 2, y = 7, z = 4
#
# Output: 1
#
# Explanation:
#
#
# 	Person 1 is at position 2 and can reach Person 3 (at position 4) in 2 steps.
# 	Person 2 is at position 7 and can reach Person 3 in 3 steps.
#
#
# Since Person 1 reaches Person 3 first, the output is 1.
#
# Constraints:
# 1 <= x, y, z <= 100
#

class Solution(object):
    def findClosest(self, x, y, z):
        """
        :type x: int
        :type y: int
        :type z: int
        :rtype: int
        """
        dist1 = abs(z - x)
        dist2 = abs(z - y)
        
        if dist1 < dist2:
            return 1
        elif dist2 < dist1:
            return 2
        else:
            return 0