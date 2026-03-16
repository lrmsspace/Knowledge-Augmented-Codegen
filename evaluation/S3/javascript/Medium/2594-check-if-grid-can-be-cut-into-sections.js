// Source: https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the dimensions of an n x n grid, with the origin at the bottom-left corner of the grid. You are also given a 2D array of coordinates rectangles, where rectangles[i] is in the form [startx, starty, endx, endy], representing a rectangle on the grid. Each rectangle is defined as follows:
//
//
// 	(startx, starty): The bottom-left corner of the rectangle.
// 	(endx, endy): The top-right corner of the rectangle.
//
//
// Note that the rectangles do not overlap. Your task is to determine if it is possible to make either two horizontal or two vertical cuts on the grid such that:
//
//
// 	Each of the three resulting sections formed by the cuts contains at least one rectangle.
// 	Every rectangle belongs to exactly one section.
//
//
// Return true if such cuts can be made; otherwise, return false.
//
// Example:
// Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
//
// Output: true
//
// Explanation:
//
//
//
// The grid is shown in the diagram. We can make horizontal cuts at y = 2 and y = 4. Hence, output is true.
//
// Constraints:
// 3 <= n <= 109
// 	3 <= rectangles.length <= 105
// 	0 <= rectangles[i][0] < rectangles[i][2] <= n
// 	0 <= rectangles[i][1] < rectangles[i][3] <= n
// 	No two rectangles overlap.
//
// Helpful references (internal KB):
// - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
//   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
//   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
//   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
//   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
//   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
// - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
//   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
//   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
//   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
//   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
//   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
// - Search for a pair of intersecting segments (geometry, tree, sweep-line)
//   • When to use: To find if any two line segments in a given set intersect, or to identify all such intersecting pairs. It is particularly efficient for problems involving geometric objects that can be ordered along a sweep axis.
//   • Idea: This algorithm processes geometric objects by sweeping a conceptual line across the plane, maintaining an ordered data structure of objects intersecting the line. It efficiently detects intersections by only checking adjacent objects in the sweep line's current state, achieving an O(N log N) time complexity.
//   • Invariants: The sweep line always moves from left to right, processing event points in strictly increasing x-coordinate order.; The data structure (e.g., balanced BST) always contains all segments currently intersecting the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
//   • Tips: Use a balanced binary search tree (e.g., `std::set`) to maintain segments on the sweep line, ordered by their y-coordinate.; Define event points (segment endpoints) and process them in increasing x-coordinate order.
//   • Pitfalls: Incorrectly handling vertical segments, which might not intersect the sweep line in a single point or have ambiguous y-order.; Floating point precision issues when comparing y-coordinates or intersection points, leading to incorrect ordering or missed intersections.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} rectangles
 * @return {boolean}
 */
var checkValidCuts = function(n, rectangles) {
    const horizontalCuts = new Set();
    const verticalCuts = new Set();
    for (const [x1, y1, x2, y2] of rectangles) {
        horizontalCuts.add(y1);
        horizontalCuts.add(y2);
        verticalCuts.add(x1);
        verticalCuts.add(x2);
    }
    return horizontalCuts.size > 1 && verticalCuts.size > 1;
};
