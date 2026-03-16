# Source: https://leetcode.com/problems/merge-operations-for-minimum-travel-time/   |   Difficulty: Hard
#
# Problem Description:
# You are given a straight road of length l km, an integer n, an integer k, and two integer arrays, position and time, each of length n.
#
# The array position lists the positions (in km) of signs in strictly increasing order (with position[0] = 0 and position[n - 1] = l).
#
# Each time[i] represents the time (in minutes) required to travel 1 km between position[i] and position[i + 1].
#
# You must perform exactly k merge operations. In one merge, you can choose any two adjacent signs at indices i and i + 1 (with i > 0 and i + 1 < n) and:
#
#
#  Update the sign at index i + 1 so that its time becomes time[i] + time[i + 1].
#  Remove the sign at index i.
#
#
# Return the minimum total travel time (in minutes) to travel from 0 to l after exactly k merges.
#
# Example:
# Input: l = 10, n = 4, k = 1, position = [0,3,8,10], time = [5,8,3,6]
#
# Output: 62
#
# Explanation:
#
#
#  
#  Merge the signs at indices 1 and 2. Remove the sign at index 1, and change the time at index 2 to 8 + 3 = 11.
#  
#  After the merge:
#  
#   position array: [0, 8, 10]
#   time array: [5, 11, 6]
#    
#  
#  
#  
#  
#   
#    
#     Segment
#     Distance (km)
#     Time per km (min)
#     Segment Travel Time (min)
#    
#   
#   
#    
#     0 → 8
#     8
#     5
#     8 × 5 = 40
#    
#    
#     8 → 10
#     2
#     11
#     2 × 11 = 22
#    
#   
#  
#  
#  Total Travel Time: 40 + 22 = 62, which is the minimum possible time after exactly 1 merge.
#
# Constraints:
# 1 <= l <= 105
#  2 <= n <= min(l + 1, 50)
#  0 <= k <= min(n - 2, 10)
#  position.length == n
#  position[0] = 0 and position[n - 1] = l
#  position is sorted in strictly increasing order.
#  time.length == n
#  1 <= time[i] <= 100​
#  1 <= sum(time) <= 100​​​​​​
#
# Helpful references (internal KB):
# - interval-dp (array, interval-dp)
#   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
#   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
#   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
#   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Knuth's Optimization (array, interval, dp-2d)
#   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
#   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
#   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minTravelTime(self, l, n, k, position, time):
        """
        :type l: int
        :type n: int
        :type k: int
        :type position: List[int]
        :type time: List[int]
        :rtype: int
        """
        # Step 1: Calculate the distance between signs
        dist = [position[i + 1] - position[i] for i in range(n - 1)]

        # Step 2: Initialize DP table
        dp = [[float('inf')] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = 0

        # Step 3: Fill DP table using interval DP
        for length in range(2, n + 1):  # length of the interval
            for i in range(n - length + 1):
                j = i + length - 1
                # Calculate the cost of merging signs from i to j
                total_time = sum(time[i:j])  # time for the current interval
                total_dist = sum(dist[i:j])   # distance for the current interval
                dp[i][j] = total_time * total_dist

                # Try merging at different points
                for m in range(i, j):
                    dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j])

        return dp[0][n - 1]