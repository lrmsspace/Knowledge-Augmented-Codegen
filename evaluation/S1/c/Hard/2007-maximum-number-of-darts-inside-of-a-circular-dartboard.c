// Source: https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/   |   Difficulty: Hard
//
// Problem Description:
// Alice is throwing n darts on a very large wall. You are given an array darts where darts[i] = [xi, yi] is the position of the ith dart that Alice threw on the wall.
//
// Bob knows the positions of the n darts on the wall. He wants to place a dartboard of radius r on the wall so that the maximum number of darts that Alice throws lie on the dartboard.
//
// Given the integer r, return the maximum number of darts that can lie on the dartboard.
//
// Example:
// Input: darts = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
// Output: 4
// Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
//
// Constraints:
// 1 <= darts.length <= 100
// 	darts[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the darts are unique
// 	1 <= r <= 5000
//
// Helpful references (internal KB):
// - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
//   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
//   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
//   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
//   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
//   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numPoints(int** darts, int dartsSize, int* dartsColSize, int r) {
    int maxCount = 1;
    for (int i = 0; i < dartsSize; i++) {
        for (int j = i + 1; j < dartsSize; j++) {
            int x1 = darts[i][0], y1 = darts[i][1];
            int x2 = darts[j][0], y2 = darts[j][1];
            int dx = x2 - x1, dy = y2 - y1;
            long long d2 = (long long)dx * dx + (long long)dy * dy;
            long long r2 = (long long)r * r;
            if (d2 > 4 * r2) continue; // No intersection
            double mx = (x1 + x2) / 2.0;
            double my = (y1 + y2) / 2.0;
            double distToMidSq = r2 - d2 / 4.0;
            double offsetX = -dy * sqrt(distToMidSq) / sqrt(d2);
            double offsetY = dx * sqrt(distToMidSq) / sqrt(d2);
            double centers[2][2] = {
                {mx + offsetX, my + offsetY},
                {mx - offsetX, my - offsetY}
            };
            for (int c = 0; c < 2; c++) {
                double cx = centers[c][0];
                double cy = centers[c][1];
                int count = 0;
                for (int k = 0; k < dartsSize; k++) {
                    double ddx = darts[k][0] - cx;
                    double ddy = darts[k][1] - cy;
                    if (ddx * ddx + ddy * ddy <= r2 + 1e-9) {
                        count++;
                    }
                }
                if (count > maxCount) {
                    maxCount = count;
                }
            }
        }
    }
    return maxCount;        
}
