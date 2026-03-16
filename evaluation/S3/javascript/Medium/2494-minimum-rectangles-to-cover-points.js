// Source: https://leetcode.com/problems/minimum-rectangles-to-cover-points/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array points, where points[i] = [xi, yi]. You are also given an integer w. Your task is to cover all the given points with rectangles.
//
// Each rectangle has its lower end at some point (x1, 0) and its upper end at some point (x2, y2), where x1 <= x2, y2 >= 0, and the condition x2 - x1 <= w must be satisfied for each rectangle.
//
// A point is considered covered by a rectangle if it lies within or on the boundary of the rectangle.
//
// Return an integer denoting the minimum number of rectangles needed so that each point is covered by at least one rectangle.
//
// Note: A point may be covered by more than one rectangle.
//
// Example:
// Input: points = [[2,1],[1,0],[1,4],[1,8],[3,5],[4,6]], w = 1
//
// Output: 2
//
// Explanation: 
//
// The image above shows one possible placement of rectangles to cover the points:
//
//
// 	A rectangle with a lower end at (1, 0) and its upper end at (2, 8)
// 	A rectangle with a lower end at (3, 0) and its upper end at (4, 8)
//
// Constraints:
// 1 <= points.length <= 105
// 	points[i].length == 2
// 	0 <= xi == points[i][0] <= 109
// 	0 <= yi == points[i][1] <= 109
// 	0 <= w <= 109
// 	All pairs (xi, yi) are distinct.
//
// Helpful references (internal KB):
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Vertical decomposition (geometry, interval, sweep-line, counting)
//   • When to use: Use when a geometric problem involves complex shapes or their unions, and partitioning the plane into simpler, independent vertical regions simplifies computation. It's particularly effective when intersections create many critical vertical boundaries.
//   • Idea: Vertical decomposition partitions a geometric plane into vertical stripes by drawing lines through critical points like vertices and segment intersections. This transforms complex intersection problems into simpler, independent subproblems within each stripe, often solvable with a sweep-line algorithm, typically resulting in O(N^2) stripes.
//   • Invariants: All critical x-coordinates (vertices, segment intersections) are identified and sorted to define stripe boundaries.; Within any given vertical stripe, no two input segments intersect.
//   • Tips: Identify all critical x-coordinates for vertical lines (vertices, segment intersections).; Sort critical x-coordinates to define the vertical stripe boundaries.
//   • Pitfalls: The O(N^2) number of stripes can lead to high complexity for large N.; Precisely handling floating-point arithmetic for intersection points is crucial.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} points
 * @param {number} w
 * @return {number}
 */
var minRectanglesToCoverPoints = function(points, w) {
    points.sort((a, b) => a[0] - b[0]);
    let rectangles = 0;
    let i = 0;

    while (i < points.length) {
        rectangles++;
        const startX = points[i][0];
        const endX = startX + w;

        // Move i to the rightmost point that can be covered by the current rectangle
        while (i < points.length && points[i][0] <= endX) {
            i++;
        }
    }

    return rectangles;
};
