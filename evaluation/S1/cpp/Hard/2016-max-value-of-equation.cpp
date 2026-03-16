// Source: https://leetcode.com/problems/max-value-of-equation/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points containing the coordinates of points on a 2D plane, sorted by the x-values, where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You are also given an integer k.
//
// Return the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
//
// It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.
//
// Example:
// Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
// Output: 4
// Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 + |1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1.
// No other pairs satisfy the condition, so we return the max of 4 and 1.
//
// Constraints:
// 2 <= points.length <= 105
// 	points[i].length == 2
// 	-108 <= xi, yi <= 108
// 	0 <= k <= 2 * 108
// 	xi < xj for all 1 <= i < j <= points.length
// 	xi form a strictly increasing sequence.
//
// Helpful references (internal KB):
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
//   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
//   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
//   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
//   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
//   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        int res = INT_MIN;
        deque<pair<int, int>> dq; // pair of (y - x, x)

        for (const auto& point : points) {
            int xj = point[0];
            int yj = point[1];

            // Remove points from the front that are out of the k range
            while (!dq.empty() && xj - dq.front().second > k) {
                dq.pop_front();
            }

            // Calculate potential result with the best candidate in the deque
            if (!dq.empty()) {
                res = max(res, yj + xj + dq.front().first);
            }

            // Maintain deque in decreasing order of (y - x)
            int currValue = yj - xj;
            while (!dq.empty() && dq.back().first <= currValue) {
                dq.pop_back();
            }
            dq.emplace_back(currValue, xj);
        }

        return res;         
    }
};
