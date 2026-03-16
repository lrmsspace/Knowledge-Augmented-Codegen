# Source: https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given three positive integers n, x, and y.
#
# In a city, there exist houses numbered 1 to n connected by n streets. There is a street connecting the house numbered i with the house numbered i + 1 for all 1 <= i <= n - 1 . An additional street connects the house numbered x with the house numbered y.
#
# For each k, such that 1 <= k <= n, you need to find the number of pairs of houses (house1, house2) such that the minimum number of streets that need to be traveled to reach house2 from house1 is k.
#
# Return a 1-indexed array result of length n where result[k] represents the total number of pairs of houses such that the minimum streets required to reach one house from the other is k.
#
# Note that x and y can be equal.
#
# Example:
# Input: n = 3, x = 1, y = 3
# Output: [6,0,0]
# Explanation: Let's look at each pair of houses:
# - For the pair (1, 2), we can go from house 1 to house 2 directly.
# - For the pair (2, 1), we can go from house 2 to house 1 directly.
# - For the pair (1, 3), we can go from house 1 to house 3 directly.
# - For the pair (3, 1), we can go from house 3 to house 1 directly.
# - For the pair (2, 3), we can go from house 2 to house 3 directly.
# - For the pair (3, 2), we can go from house 3 to house 2 directly.
#
# Constraints:
# 2 <= n <= 100
# 	1 <= x, y <= n
#
# Helpful references (internal KB):
# - Length of the union of segments (array, interval, sweep-line, counting)
#   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
#   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
#   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
#   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
#   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
# - Binomial Coefficients (number, enumeration)
#   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
#   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
#   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
#   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
#   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countOfPairs(self, n, x, y):
        """
        :type n: int
        :type x: int
        :type y: int
        :rtype: List[int]
        """
        from collections import defaultdict

        distance_count = defaultdict(int)

        for house1 in range(1, n + 1):
            for house2 in range(house1 + 1, n + 1):
                direct_distance = abs(house2 - house1)
                via_xy_distance = abs(house1 - x) + 1 + abs(y - house2)
                min_distance = min(direct_distance, via_xy_distance)
                distance_count[min_distance] += 2  # Count both (house1, house2) and (house2, house1)

        result = [0] * n
        for k in range(1, n + 1):
            result[k - 1] = distance_count[k]

        return result