# Source: https://leetcode.com/problems/boats-to-save-people/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array people where people[i] is the weight of the ith person, and an infinite number of boats where each boat can carry a maximum weight of limit. Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.
#
# Return the minimum number of boats to carry every given person.
#
# Example:
# Input: people = [1,2], limit = 3
# Output: 1
# Explanation: 1 boat (1, 2)
#
# Constraints:
# 1 <= people.length <= 5 * 104
# 	1 <= people[i] <= limit <= 3 * 104
#

class Solution(object):
    def numRescueBoats(self, people, limit):
        """
        :type people: List[int]
        :type limit: int
        :rtype: int
        """
        people.sort()
        left, right = 0, len(people) - 1
        boats = 0
        
        while left <= right:
            if people[left] + people[right] <= limit:
                left += 1
            right -= 1
            boats += 1
            
        return boats