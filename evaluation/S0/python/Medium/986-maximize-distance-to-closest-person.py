# Source: https://leetcode.com/problems/maximize-distance-to-closest-person/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array representing a row of seats where seats[i] = 1 represents a person sitting in the ith seat, and seats[i] = 0 represents that the ith seat is empty (0-indexed).
#
# There is at least one empty seat, and at least one person sitting.
#
# Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized. 
#
# Return that maximum distance to the closest person.
#
# Example:
# Input: seats = [1,0,0,0,1,0,1]
# Output: 2
# Explanation: 
# If Alex sits in the second open seat (i.e. seats[2]), then the closest person has distance 2.
# If Alex sits in any other open seat, the closest person has distance 1.
# Thus, the maximum distance to the closest person is 2.
#
# Constraints:
# 2 <= seats.length <= 2 * 104
# 	seats[i] is 0 or 1.
# 	At least one seat is empty.
# 	At least one seat is occupied.
#

class Solution(object):
    def maxDistToClosest(self, seats):
        """
        :type seats: List[int]
        :rtype: int
        """
        n = len(seats)
        max_distance = 0
        last_person = -1

        for i in range(n):
            if seats[i] == 1:
                if last_person == -1:
                    max_distance = i  # Distance from the start to the first person
                else:
                    max_distance = max(max_distance, (i - last_person) // 2)
                last_person = i

        # Check distance from the last person to the end
        max_distance = max(max_distance, n - 1 - last_person)

        return max_distance