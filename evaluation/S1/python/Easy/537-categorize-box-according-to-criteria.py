# Source: https://leetcode.com/problems/categorize-box-according-to-criteria/   |   Difficulty: Easy
#
# Problem Description:
# Given four integers length, width, height, and mass, representing the dimensions and mass of a box, respectively, return a string representing the category of the box.
#
#
# 	The box is "Bulky" if:
#
# 	
# 		Any of the dimensions of the box is greater or equal to 104.
# 		Or, the volume of the box is greater or equal to 109.
# 	
# 	
# 	If the mass of the box is greater or equal to 100, it is "Heavy".
# 	If the box is both "Bulky" and "Heavy", then its category is "Both".
# 	If the box is neither "Bulky" nor "Heavy", then its category is "Neither".
# 	If the box is "Bulky" but not "Heavy", then its category is "Bulky".
# 	If the box is "Heavy" but not "Bulky", then its category is "Heavy".
#
#
# Note that the volume of the box is the product of its length, width and height.
#
# Example:
# Input: length = 1000, width = 35, height = 700, mass = 300
# Output: "Heavy"
# Explanation: 
# None of the dimensions of the box is greater or equal to 104. 
# Its volume = 24500000 <= 109. So it cannot be categorized as "Bulky".
# However mass >= 100, so the box is "Heavy".
# Since the box is not "Bulky" but "Heavy", we return "Heavy".
#
# Constraints:
# 1 <= length, width, height <= 105
# 	1 <= mass <= 103
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
    def categorizeBox(self, length, width, height, mass):
        """
        :type length: int
        :type width: int
        :type height: int
        :type mass: int
        :rtype: str
        """
        is_bulky = length >= 10**4 or width >= 10**4 or height >= 10**4 or length * width * height >= 10**9
        is_heavy = mass >= 100
        
        if is_bulky and is_heavy:
            return "Both"
        elif is_bulky:
            return "Bulky"
        elif is_heavy:
            return "Heavy"
        else:
            return "Neither"