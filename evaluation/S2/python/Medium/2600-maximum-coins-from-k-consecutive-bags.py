# Source: https://leetcode.com/problems/maximum-coins-from-k-consecutive-bags/   |   Difficulty: Medium
#
# Problem Description:
# There are an infinite amount of bags on a number line, one bag for each coordinate. Some of these bags contain coins.
#
# You are given a 2D array coins, where coins[i] = [li, ri, ci] denotes that every bag from li to ri contains ci coins.
#
# The segments that coins contain are non-overlapping.
#
# You are also given an integer k.
#
# Return the maximum amount of coins you can obtain by collecting k consecutive bags.
#
# Example:
# Input: coins = [[8,10,1],[1,3,2],[5,6,4]], k = 4
#
# Output: 10
#
# Explanation:
#
# Selecting bags at positions [3, 4, 5, 6] gives the maximum number of coins: 2 + 0 + 4 + 4 = 10.
#
# Constraints:
# 1 <= coins.length <= 105
# 	1 <= k <= 109
# 	coins[i] == [li, ri, ci]
# 	1 <= li <= ri <= 109
# 	1 <= ci <= 1000
# 	The given segments are non-overlapping.
#
# Helpful references (internal KB):
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# - Length of the union of segments (array, interval, sweep-line, counting)
#   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
#   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
#   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
#   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
#   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
# - Convex hull trick and Li Chao tree (number, segment-tree, recursion)
#   • When to use: Used to find the minimum (or maximum) value among a set of linear functions at a given point. It is particularly efficient for dynamic sets of lines or when slopes are monotonic.
#   • Idea: The Convex Hull Trick (CHT) and Li Chao Tree efficiently find the minimum (or maximum) value of a set of linear functions at a query point. CHT typically achieves O(log N) or O(1) amortized time, while Li Chao Tree offers O(log C) for updates and queries.
#   • Invariants: In CHT, the lower envelope of lines forms a convex shape, with slopes monotonically ordered.; In Li Chao Tree, each node stores a line that is optimal at the segment's midpoint for lines added to that node.
#   • Tips: Ensure slopes are monotonic for efficient CHT implementations.; Li Chao Tree handles non-monotonic slopes but requires a coordinate range.
#   • Pitfalls: Floating point precision issues can lead to incorrect intersection calculations.; Incorrectly managing the convex hull structure (e.g., deque) in CHT.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumCoins(self, coins, k):
        """
        :type coins: List[List[int]]
        :type k: int
        :rtype: int
        """
        # Step 1: Calculate the total coins in each bag using a sweep line algorithm
        events = []
        for l, r, c in coins:
            events.append((l, c))   # Start of segment adds coins
            events.append((r + 1, -c))  # End of segment subtracts coins

        # Sort events by position; if tie, start events come before end events
        events.sort(key=lambda x: (x[0], -x[1]))

        bag_coins = {}
        current_coins = 0
        prev_position = 0

        for position, coin_change in events:
            if position > prev_position:
                bag_coins[prev_position] = current_coins
                prev_position = position
            current_coins += coin_change

        # Step 2: Create a sorted list of bags and their coin counts
        sorted_bags = sorted(bag_coins.items())

        # Step 3: Use a sliding window to find the maximum coins in any k consecutive bags
        max_coins = 0
        window_sum = 0
        left = 0

        for right in range(len(sorted_bags)):
            window_sum += sorted_bags[right][1]

            while sorted_bags[right][0] - sorted_bags[left][0] >= k:
                window_sum -= sorted_bags[left][1]
                left += 1

            max_coins = max(max_coins, window_sum)

        return max_coins