// Source: https://leetcode.com/problems/count-number-of-rectangles-containing-each-point/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array rectangles where rectangles[i] = [li, hi] indicates that ith rectangle has a length of li and a height of hi. You are also given a 2D integer array points where points[j] = [xj, yj] is a point with coordinates (xj, yj).
//
// The ith rectangle has its bottom-left corner point at the coordinates (0, 0) and its top-right corner point at (li, hi).
//
// Return an integer array count of length points.length where count[j] is the number of rectangles that contain the jth point.
//
// The ith rectangle contains the jth point if 0 <= xj <= li and 0 <= yj <= hi. Note that points that lie on the edges of a rectangle are also considered to be contained by that rectangle.
//
// Example:
// Input: rectangles = [[1,2],[2,3],[2,5]], points = [[2,1],[1,4]]
// Output: [2,1]
// Explanation: 
// The first rectangle contains no points.
// The second rectangle contains only the point (2, 1).
// The third rectangle contains the points (2, 1) and (1, 4).
// The number of rectangles that contain the point (2, 1) is 2.
// The number of rectangles that contain the point (1, 4) is 1.
// Therefore, we return [2, 1].
//
// Constraints:
// 1 <= rectangles.length, points.length <= 5 * 104
// 	rectangles[i].length == points[j].length == 2
// 	1 <= li, xj <= 109
// 	1 <= hi, yj <= 100
// 	All the rectangles are unique.
// 	All the points are unique.
//
// Helpful references (internal KB):
// - Check if point belongs to the convex pol (geometry, array, binary-search)
//   • When to use: This algorithm is used to efficiently determine if a given query point lies inside or on the boundary of a convex polygon, especially when many queries are performed on the same polygon.
//   • Idea: The core idea is to decompose the convex polygon into triangles originating from a reference vertex. Binary search is then used to find the specific triangle that could contain the query point, followed by a point-in-triangle check.
//   • Invariants: The reference point p_0 is the lexicographically smallest vertex of the polygon.; All polygon vertices p_1, ..., p_n are ordered counter-clockwise by polar angle around p_0.
//   • Tips: Choose a consistent reference point, typically the lexicographically smallest vertex, to simplify angular sorting.; Ensure polygon vertices are ordered (e.g., counter-clockwise) relative to the reference point for correct binary search behavior.
//   • Pitfalls: Floating point precision errors can lead to incorrect results for collinear points or boundary checks; prefer integer arithmetic with cross products.; Incorrectly handling boundary conditions (points exactly on an edge or vertex) can lead to false negatives or positives.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} rectangles
 * @param {number[][]} points
 * @return {number[]}
 */
var countRectangles = function(rectangles, points) {
    const heightBuckets = Array.from({ length: 101 }, () => []);
    for (const [length, height] of rectangles) {
        heightBuckets[height].push(length);
    }

    for (let h = 1; h <= 100; h++) {
        heightBuckets[h].sort((a, b) => a - b);
    }

    const result = [];
    for (const [x, y] of points) {
        let count = 0;
        for (let h = y; h <= 100; h++) {
            const lengths = heightBuckets[h];
            let left = 0;
            let right = lengths.length;
            while (left < right) {
                const mid = Math.floor((left + right) / 2);
                if (lengths[mid] >= x) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            count += lengths.length - left;
        }
        result.push(count);
    }

    return result;
};
