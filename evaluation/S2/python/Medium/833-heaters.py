# Source: https://leetcode.com/problems/heaters/   |   Difficulty: Medium
#
# Problem Description:
# Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
#
# Every house can be warmed, as long as the house is within the heater's warm radius range. 
#
# Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
#
# Notice that all the heaters follow your radius standard, and the warm radius will be the same.
#
# Example:
# Input: houses = [1,2,3], heaters = [2]
# Output: 1
# Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
#
# Constraints:
# 1 <= houses.length, heaters.length <= 3 * 104
# 	1 <= houses[i], heaters[i] <= 109
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
    def findRadius(self, houses, heaters):
        """
        :type houses: List[int]
        :type heaters: List[int]
        :rtype: int
        """
        heaters.sort()
        radius = 0

        for house in houses:
            # Binary search to find the closest heater
            left, right = 0, len(heaters) - 1
            while left < right:
                mid = (left + right) // 2
                if heaters[mid] < house:
                    left = mid + 1
                else:
                    right = mid

            # Check the distance to the closest heater on the left and right
            dist_left = abs(house - heaters[left]) if left < len(heaters) else float('inf')
            dist_right = abs(house - heaters[left - 1]) if left > 0 else float('inf')

            # Update the radius needed for this house
            radius = max(radius, min(dist_left, dist_right))

        return radius