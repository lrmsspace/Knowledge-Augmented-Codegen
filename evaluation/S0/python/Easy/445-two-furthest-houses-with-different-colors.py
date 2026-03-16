# Source: https://leetcode.com/problems/two-furthest-houses-with-different-colors/   |   Difficulty: Easy
#
# Problem Description:
# There are n houses evenly lined up on the street, and each house is beautifully painted. You are given a 0-indexed integer array colors of length n, where colors[i] represents the color of the ith house.
#
# Return the maximum distance between two houses with different colors.
#
# The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.
#
# Example:
# Input: colors = [1,1,1,6,1,1,1]
# Output: 3
# Explanation: In the above image, color 1 is blue, and color 6 is red.
# The furthest two houses with different colors are house 0 and house 3.
# House 0 has color 1, and house 3 has color 6. The distance between them is abs(0 - 3) = 3.
# Note that houses 3 and 6 can also produce the optimal answer.
#
# Constraints:
# n == colors.length
# 	2 <= n <= 100
# 	0 <= colors[i] <= 100
# 	Test data are generated such that at least two houses have different colors.
#

class Solution(object):
    def maxDistance(self, colors):
        """
        :type colors: List[int]
        :rtype: int
        """
        left = 0
        right = len(colors) - 1
        
        max_dist = 0
        
        while left < right:
            if colors[left] != colors[right]:
                max_dist = max(max_dist, right - left)
                # Move both pointers inward to potentially find a larger distance
                left += 1
                right -= 1
            else:
                # Move the pointer that might lead to a different color
                if colors[left + 1] != colors[left]:
                    left += 1
                else:
                    right -= 1
        
        return max_dist