// Source: https://leetcode.com/problems/perfect-rectangle/   |   Difficulty: Hard
//
// Problem Description:
// Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
//
// Return true if all the rectangles together form an exact cover of a rectangular region.
//
// Example:
// Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
// Output: true
// Explanation: All 5 rectangles together form an exact cover of a rectangular region.
//
// Constraints:
// 1 <= rectangles.length <= 2 * 104
// 	rectangles[i].length == 4
// 	-105 <= xi < ai <= 105
// 	-105 <= yi < bi <= 105
//
// Helpful references (internal KB):
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Manhattan Distance (geometry, graph, sweep-line, mst-kruskal, coordinate-compress)
//   • When to use: Use this when finding the Minimum Spanning Tree for points in a 2D plane where edge weights are Manhattan distances, or when a geometric problem can be simplified by transforming Manhattan to Chebyshev distance.
//   • Idea: This algorithm finds the Minimum Spanning Tree for points in a 2D plane using Manhattan distance. It leverages a sweep-line approach to efficiently find nearest neighbors in specific octants, reducing the number of candidate edges for Kruskal's algorithm, achieving O(N log N) complexity.
//   • Invariants: For any point 's' in the active set, its nearest neighbor in the current octant has not yet been processed.; Points are processed in non-decreasing order of 'x + y' (or transformed coordinate), ensuring local optimality for distances.
//   • Tips: Consider transforming Manhattan distance problems into Chebyshev distance problems using (x+y, y-x) coordinates.; Divide the plane into 8 octants around each point to simplify nearest neighbor searches.
//   • Pitfalls: Incorrectly defining or handling the 8 octants, especially near boundaries or for points with equal coordinates.; Inefficiently managing the 'active set' during the sweep-line, leading to higher than O(N log N) complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} rectangles
 * @return {boolean}
 */
var isRectangleCover = function(rectangles) {
    let minX = Infinity, minY = Infinity, maxX = -Infinity, maxY = -Infinity;
    let areaSum = 0;
    const points = new Set();
    
    for (const [x1, y1, x2, y2] of rectangles) {
        minX = Math.min(minX, x1);
        minY = Math.min(minY, y1);
        maxX = Math.max(maxX, x2);
        maxY = Math.max(maxY, y2);
        
        areaSum += (x2 - x1) * (y2 - y1);
        
        const corners = [[x1, y1], [x2, y1], [x1, y2], [x2, y2]];
        for (const corner of corners) {
            const key = corner.toString();
            if (points.has(key)) {
                points.delete(key);
            } else {
                points.add(key);
            }
        }
    }
    
    const expectedArea = (maxX - minX) * (maxY - minY);
    if (areaSum !== expectedArea) return false;
    
    const expectedCorners = new Set([
        [minX, minY].toString(),
        [minX, maxY].toString(),
        [maxX, minY].toString(),
        [maxX, maxY].toString()
    ]);
    
    if (points.size !== 4) return false;
    
    for (const corner of expectedCorners) {
        if (!points.has(corner)) return false;
    }
    
    return true;
};
