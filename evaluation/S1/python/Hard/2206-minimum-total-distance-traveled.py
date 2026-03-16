# Source: https://leetcode.com/problems/minimum-total-distance-traveled/   |   Difficulty: Hard
#
# Problem Description:
# There are some robots and factories on the X-axis. You are given an integer array robot where robot[i] is the position of the ith robot. You are also given a 2D integer array factory where factory[j] = [positionj, limitj] indicates that positionj is the position of the jth factory and that the jth factory can repair at most limitj robots.
#
# The positions of each robot are unique. The positions of each factory are also unique. Note that a robot can be in the same position as a factory initially.
#
# All the robots are initially broken; they keep moving in one direction. The direction could be the negative or the positive direction of the X-axis. When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.
#
# At any moment, you can set the initial direction of moving for some robot. Your target is to minimize the total distance traveled by all the robots.
#
# Return the minimum total distance traveled by all the robots. The test cases are generated such that all the robots can be repaired.
#
# Note that
#
#
# 	All robots move at the same speed.
# 	If two robots move in the same direction, they will never collide.
# 	If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
# 	If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
# 	If the robot moved from a position x to a position y, the distance it moved is |y - x|.
#
# Example:
# Input: robot = [0,4,6], factory = [[2,2],[6,2]]
# Output: 4
# Explanation: As shown in the figure:
# - The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
# - The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
# - The third robot at position 6 will be repaired at the second factory. It does not need to move.
# The limit of the first factory is 2, and it fixed 2 robots.
# The limit of the second factory is 2, and it fixed 1 robot.
# The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.
#
# Constraints:
# 1 <= robot.length, factory.length <= 100
# 	factory[j].length == 2
# 	-109 <= robot[i], positionj <= 109
# 	0 <= limitj <= robot.length
# 	The input will be generated such that it is always possible to repair every robot.
#
# Helpful references (internal KB):
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumTotalDistance(self, robot, factory):
        """
        :type robot: List[int]
        :type factory: List[List[int]]
        :rtype: int
        """
        robot.sort()
        factory.sort(key=lambda x: x[0])
        m, n = len(robot), len(factory)

        # dp[i][j] = minimum total distance to fix first i robots with first j factories
        dp = [[float('inf')] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = 0

        for j in range(1, n + 1):
            dp[0][j] = 0  # No robots to fix, no distance

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                dp[i][j] = dp[i][j - 1]  # Skip current factory
                limit = factory[j - 1][1]
                for k in range(1, min(i, limit) + 1):
                    dp[i][j] = min(dp[i][j], dp[i - k][j - 1] + sum(abs(robot[i - l - 1] - factory[j - 1][0]) for l in range(k)))

        return dp[m][n]