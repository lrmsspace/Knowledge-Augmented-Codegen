# Source: https://leetcode.com/problems/maximum-building-height/   |   Difficulty: Hard
#
# Problem Description:
# You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.
#
# However, there are city restrictions on the heights of the new buildings:
#
#
# 	The height of each building must be a non-negative integer.
# 	The height of the first building must be 0.
# 	The height difference between any two adjacent buildings cannot exceed 1.
#
#
# Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.
#
# It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.
#
# Return the maximum possible height of the tallest building.
#
# Example:
# Input: n = 5, restrictions = [[2,1],[4,1]]
# Output: 2
# Explanation: The green area in the image indicates the maximum allowed height for each building.
# We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
#
# Constraints:
# 2 <= n <= 109
# 	0 <= restrictions.length <= min(n - 1, 105)
# 	2 <= idi <= n
# 	idi is unique.
# 	0 <= maxHeighti <= 109
#
# Helpful references (internal KB):
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
# - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
#   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
#   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
#   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
#   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
#   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxBuilding(self, n, restrictions):
        """
        :type n: int
        :type restrictions: List[List[int]]
        :rtype: int
        """
        restrictions.append([1, 0])
        restrictions.append([n, n - 1])
        restrictions.sort()

        for i in range(1, len(restrictions)):
            prev_id, prev_max = restrictions[i - 1]
            curr_id, curr_max = restrictions[i]
            max_possible = prev_max + (curr_id - prev_id)
            if curr_max > max_possible:
                restrictions[i][1] = max_possible

        for i in range(len(restrictions) - 2, -1, -1):
            next_id, next_max = restrictions[i + 1]
            curr_id, curr_max = restrictions[i]
            max_possible = next_max + (next_id - curr_id)
            if curr_max > max_possible:
                restrictions[i][1] = max_possible

        ans = 0
        for i in range(1, len(restrictions)):
            prev_id, prev_max = restrictions[i - 1]
            curr_id, curr_max = restrictions[i]
            distance = curr_id - prev_id
            height_diff = abs(curr_max - prev_max)

            if distance >= height_diff:
                extra_height = (distance - height_diff) // 2
                ans = max(ans, max(curr_max, prev_max) + extra_height)
            else:
                ans = max(ans, min(curr_max, prev_max) + distance)

        return ans