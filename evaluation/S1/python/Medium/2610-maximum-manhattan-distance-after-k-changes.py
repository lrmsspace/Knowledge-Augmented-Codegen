# Source: https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s consisting of the characters 'N', 'S', 'E', and 'W', where s[i] indicates movements in an infinite grid:
#
#
# 	'N' : Move north by 1 unit.
# 	'S' : Move south by 1 unit.
# 	'E' : Move east by 1 unit.
# 	'W' : Move west by 1 unit.
#
#
# Initially, you are at the origin (0, 0). You can change at most k characters to any of the four directions.
#
# Find the maximum Manhattan distance from the origin that can be achieved at any time while performing the movements in order.
# The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
#
# Example:
# Input: s = "NWSE", k = 1
#
# Output: 3
#
# Explanation:
#
# Change s[2] from 'S' to 'N'. The string s becomes "NWNE".
#
#
# 	
# 		
# 			Movement
# 			Position (x, y)
# 			Manhattan Distance
# 			Maximum
# 		
# 	
# 	
# 		
# 			s[0] == 'N'
# 			(0, 1)
# 			0 + 1 = 1
# 			1
# 		
# 		
# 			s[1] == 'W'
# 			(-1, 1)
# 			1 + 1 = 2
# 			2
# 		
# 		
# 			s[2] == 'N'
# 			(-1, 2)
# 			1 + 2 = 3
# 			3
# 		
# 		
# 			s[3] == 'E'
# 			(0, 2)
# 			0 + 2 = 2
# 			3
# 		
# 	
#
#
# The maximum Manhattan distance from the origin that can be achieved is 3. Hence, 3 is the output.
#
# Constraints:
# 1 <= s.length <= 105
# 	0 <= k <= s.length
# 	s consists of only 'N', 'S', 'E', and 'W'.
#
# Helpful references (internal KB):
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxDistance(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        x = y = 0
        for char in s:
            if char == 'N':
                y += 1
            elif char == 'S':
                y -= 1
            elif char == 'E':
                x += 1
            elif char == 'W':
                x -= 1

        dist = abs(x) + abs(y)

        # Each change can increase the distance by 2 if it corrects a move towards the origin
        max_increase = 2 * k

        return dist + max_increase