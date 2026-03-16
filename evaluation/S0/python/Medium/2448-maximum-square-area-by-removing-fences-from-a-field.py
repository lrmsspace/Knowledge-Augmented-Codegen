# Source: https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/   |   Difficulty: Medium
#
# Problem Description:
# There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.
#
# Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).
#
# Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.
#
# Example:
# Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
# Output: 4
# Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.
#
# Constraints:
# 3 <= m, n <= 109
# 	1 <= hFences.length, vFences.length <= 600
# 	1 < hFences[i] < m
# 	1 < vFences[i] < n
# 	hFences and vFences are unique.
#

class Solution(object):
    def maximizeSquareArea(self, m, n, hFences, vFences):
        """
        :type m: int
        :type n: int
        :type hFences: List[int]
        :type vFences: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # Add the boundaries
        hFences = [1] + sorted(hFences) + [m]
        vFences = [1] + sorted(vFences) + [n]
        
        # Calculate maximum gaps
        max_h_gap = max(hFences[i] - hFences[i-1] for i in range(1, len(hFences)))
        max_v_gap = max(vFences[i] - vFences[i-1] for i in range(1, len(vFences)))
        
        # The side of the largest square is the minimum of the two maximum gaps
        side_length = min(max_h_gap, max_v_gap)
        
        # If side_length is less than 2, we cannot form a square field
        if side_length < 2:
            return -1
        
        # Return the area modulo MOD
        return (side_length - 1) * (side_length - 1) % MOD