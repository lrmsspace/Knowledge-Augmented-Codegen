// Source: https://leetcode.com/problems/coordinate-with-maximum-network-quality/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of network towers towers, where towers[i] = [xi, yi, qi] denotes the ith network tower with location (xi, yi) and quality factor qi. All the coordinates are integral coordinates on the X-Y plane, and the distance between the two coordinates is the Euclidean distance.
//
// You are also given an integer radius where a tower is reachable if the distance is less than or equal to radius. Outside that distance, the signal becomes garbled, and the tower is not reachable.
//
// The signal quality of the ith tower at a coordinate (x, y) is calculated with the formula ⌊qi / (1 + d)⌋, where d is the distance between the tower and the coordinate. The network quality at a coordinate is the sum of the signal qualities from all the reachable towers.
//
// Return the array [cx, cy] representing the integral coordinate (cx, cy) where the network quality is maximum. If there are multiple coordinates with the same network quality, return the lexicographically minimum non-negative coordinate.
//
// Note:
//
//
// 	A coordinate (x1, y1) is lexicographically smaller than (x2, y2) if either:
//
// 	
// 		x1 < x2, or
// 		x1 == x2 and y1 < y2.
// 	
// 	
// 	⌊val⌋ is the greatest integer less than or equal to val (the floor function).
//
// Example:
// Input: towers = [[1,2,5],[2,1,7],[3,1,9]], radius = 2
// Output: [2,1]
// Explanation: At coordinate (2, 1) the total quality is 13.
// - Quality of 7 from (2, 1) results in ⌊7 / (1 + sqrt(0)⌋ = ⌊7⌋ = 7
// - Quality of 5 from (1, 2) results in ⌊5 / (1 + sqrt(2)⌋ = ⌊2.07⌋ = 2
// - Quality of 9 from (3, 1) results in ⌊9 / (1 + sqrt(1)⌋ = ⌊4.5⌋ = 4
// No other coordinate has a higher network quality.
//
// Constraints:
// 1 <= towers.length <= 50
// 	towers[i].length == 3
// 	0 <= xi, yi, qi <= 50
// 	1 <= radius <= 50
//
// Helpful references (internal KB):
// - Minimum Enclosing Circle (array, geometry, randomized, recursion)
//   • When to use: Use when finding the smallest circle that contains a given set of 2D points. It provides an expected linear time solution for this fundamental geometric problem.
//   • Idea: Welzl's algorithm finds the unique minimum enclosing circle for a set of points using a randomized incremental approach. It achieves an expected time complexity of O(N).
//   • Invariants: The current candidate circle `C` encloses all points `p_1, ..., p_i` processed so far.; If `p_i` is not contained in `C_{i-1}`, then `p_i` must lie on the boundary of `C_i`.
//   • Tips: Randomly permute input points to ensure expected O(N) performance.; The MEC is uniquely determined by either two points forming a diameter or three points on its boundary.
//   • Pitfalls: Not randomizing the input can lead to a worst-case O(N^3) performance.; Floating-point precision issues can cause incorrect boundary checks or point containment tests.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} towers
 * @param {number} radius
 * @return {number[]}
 */
var bestCoordinate = function(towers, radius) {
    let maxQuality = 0;
    let bestCoord = [0, 0];
    for (let x = 0; x <= 50; x++) {
        for (let y = 0; y <= 50; y++) {
            let quality = 0;
            for (const [tx, ty, q] of towers) {
                const distance = Math.sqrt((x - tx) ** 2 + (y - ty) ** 2);
                if (distance <= radius) {
                    quality += Math.floor(q / (1 + distance));
                }
            }
            if (quality > maxQuality) {
                maxQuality = quality;
                bestCoord = [x, y];
            }
        }
    }
    return bestCoord;
};
