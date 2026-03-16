# Source: https://leetcode.com/problems/shift-distance-between-two-strings/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings s and t of the same length, and two integer arrays nextCost and previousCost.
#
# In one operation, you can pick any index i of s, and perform either one of the following actions:
#
#
# 	Shift s[i] to the next letter in the alphabet. If s[i] == 'z', you should replace it with 'a'. This operation costs nextCost[j] where j is the index of s[i] in the alphabet.
# 	Shift s[i] to the previous letter in the alphabet. If s[i] == 'a', you should replace it with 'z'. This operation costs previousCost[j] where j is the index of s[i] in the alphabet.
#
#
# The shift distance is the minimum total cost of operations required to transform s into t.
#
# Return the shift distance from s to t.
#
# Example:
# Input: s = "abab", t = "baba", nextCost = [100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0], previousCost = [1,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
#
# Output: 2
#
# Explanation:
#
#
# 	We choose index i = 0 and shift s[0] 25 times to the previous character for a total cost of 1.
# 	We choose index i = 1 and shift s[1] 25 times to the next character for a total cost of 0.
# 	We choose index i = 2 and shift s[2] 25 times to the previous character for a total cost of 1.
# 	We choose index i = 3 and shift s[3] 25 times to the next character for a total cost of 0.
#
# Constraints:
# 1 <= s.length == t.length <= 105
# 	s and t consist only of lowercase English letters.
# 	nextCost.length == previousCost.length == 26
# 	0 <= nextCost[i], previousCost[i] <= 109
#
# Helpful references (internal KB):
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
# - Minimum stack / Minimum queue (queue, stack, simulation)
#   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
#   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
#   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
#   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
#   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shiftDistance(self, s, t, nextCost, previousCost):
        """
        :type s: str
        :type t: str
        :type nextCost: List[int]
        :type previousCost: List[int]
        :rtype: int
        """
        total_cost = 0
        n = len(s)
        
        for i in range(n):
            if s[i] == t[i]:
                continue
            
            char_s = ord(s[i]) - ord('a')
            char_t = ord(t[i]) - ord('a')
            
            # Calculate cost for shifting forward
            if char_t >= char_s:
                forward_shifts = char_t - char_s
            else:
                forward_shifts = 26 - (char_s - char_t)
            forward_cost = sum(nextCost[(char_s + j) % 26] for j in range(1, forward_shifts + 1))
            
            # Calculate cost for shifting backward
            if char_s >= char_t:
                backward_shifts = char_s - char_t
            else:
                backward_shifts = 26 - (char_t - char_s)
            backward_cost = sum(previousCost[(char_s - j) % 26] for j in range(1, backward_shifts + 1))
            
            # Add the minimum of the two costs to total cost
            total_cost += min(forward_cost, backward_cost)
        
        return total_cost