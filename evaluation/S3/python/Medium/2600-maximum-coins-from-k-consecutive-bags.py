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
# - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
#   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
#   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
#   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
#   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
#   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
# - Convex hull trick and Li Chao tree (geometry, array, sweep-line, binary-search)
#   • When to use: When optimizing dynamic programming states that involve minimizing or maximizing linear functions, especially when slopes are monotonic or queries can be processed offline.
#   • Idea: Convex Hull Trick optimizes dynamic programming problems by maintaining a lower (or upper) convex hull of linear functions. It allows efficient querying of the minimum (or maximum) value of these functions at a given point, typically achieving O(N log N) or O(N) complexity.
#   • Invariants: The set of active lines always forms a lower (or upper) convex hull.; Lines within the hull are ordered by their slopes.
#   • Tips: Sort lines by slope for O(N) or O(N log N) insertion.; Use a deque for O(N) CHT when both slopes and query points are monotonic.
#   • Pitfalls: Incorrectly assuming monotonicity of slopes or query points.; Floating point precision issues when dealing with intersections.
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
#   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
#   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
#   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
#   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
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
        # Step 1: Create a list of events for the start and end of each coin segment
        events = []
        for l, r, c in coins:
            events.append((l, c))   # Start of a segment adds coins
            events.append((r + 1, -c))  # End of a segment removes coins

        # Step 2: Sort events by their position
        events.sort()

        # Step 3: Use a sweep line to calculate the number of coins at each position
        current_coins = 0
        last_position = 0
        coin_counts = []  # List to store (position, coins) pairs

        for position, change in events:
            if position != last_position:
                coin_counts.append((last_position, current_coins))
                last_position = position
            current_coins += change

        # Add the final position with its coin count
        coin_counts.append((last_position, current_coins))

        # Step 4: Use a sliding window to find the maximum coins in any k consecutive bags
        max_coins = 0
        window_sum = 0
        left = 0

        for right in range(len(coin_counts)):
            # Add coins from the right end of the window
            while right < len(coin_counts) and coin_counts[right][0] < coin_counts[left][0] + k:
                window_sum += coin_counts[right][1]
                right += 1
            
            # Update max coins if the current window is valid
            max_coins = max(max_coins, window_sum)

            # Remove coins from the left end of the window as we move it forward
            if right > left:
                window_sum -= coin_counts[left][1]
                left += 1

        return max_coins