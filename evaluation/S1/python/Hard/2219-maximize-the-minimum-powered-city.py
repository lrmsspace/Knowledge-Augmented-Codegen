# Source: https://leetcode.com/problems/maximize-the-minimum-powered-city/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array stations of length n, where stations[i] represents the number of power stations in the ith city.
#
# Each power station can provide power to every city in a fixed range. In other words, if the range is denoted by r, then a power station at city i can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.
#
#
# 	Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.
#
#
# The power of a city is the total number of power stations it is being provided power from.
#
# The government has sanctioned building k more power stations, each of which can be built in any city, and have the same range as the pre-existing ones.
#
# Given the two integers r and k, return the maximum possible minimum power of a city, if the additional power stations are built optimally.
#
# Note that you can build the k power stations in multiple cities.
#
# Example:
# Input: stations = [1,2,4,5,0], r = 1, k = 2
# Output: 5
# Explanation: 
# One of the optimal ways is to install both the power stations at city 1. 
# So stations will become [1,4,4,5,0].
# - City 0 is provided by 1 + 4 = 5 power stations.
# - City 1 is provided by 1 + 4 + 4 = 9 power stations.
# - City 2 is provided by 4 + 4 + 5 = 13 power stations.
# - City 3 is provided by 5 + 4 = 9 power stations.
# - City 4 is provided by 5 + 0 = 5 power stations.
# So the minimum power of a city is 5.
# Since it is not possible to obtain a larger power, we return 5.
#
# Constraints:
# n == stations.length
# 	1 <= n <= 105
# 	0 <= stations[i] <= 105
# 	0 <= r <= n - 1
# 	0 <= k <= 109
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
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
    def maxPower(self, stations, r, k):
        """
        :type stations: List[int]
        :type r: int
        :type k: int
        :rtype: int
        """
        n = len(stations)
        # Step 1: Calculate initial power for each city
        power = [0] * n
        for i in range(n):
            left_bound = max(0, i - r)
            right_bound = min(n - 1, i + r)
            power[i] += stations[i]
            if left_bound > 0:
                power[left_bound - 1] -= stations[i]
            if right_bound < n - 1:
                power[right_bound + 1] -= stations[i]

        # Prefix sum to get the actual power of each city
        for i in range(1, n):
            power[i] += power[i - 1]

        # Step 2: Binary search for the maximum minimum power
        low, high = min(power), max(power) + k
        while low < high:
            mid = (low + high + 1) // 2
            needed_stations = 0
            current_power = power[:]
            for i in range(n):
                if current_power[i] < mid:
                    needed_stations += mid - current_power[i]
                    if needed_stations > k:
                        break
                    # Distribute the needed stations to the right
                    add_power = mid - current_power[i]
                    current_power[i] += add_power
                    if i + r + 1 < n:
                        current_power[i + r + 1] -= add_power

            if needed_stations <= k:
                low = mid
            else:
                high = mid - 1

        return low