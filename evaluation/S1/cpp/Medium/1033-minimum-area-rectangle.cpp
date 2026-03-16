// Source: https://leetcode.com/problems/minimum-area-rectangle/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
//
// Return the minimum area of a rectangle formed from these points, with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.
//
// Example:
// Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
// Output: 4
//
// Constraints:
// 1 <= points.length <= 500
// 	points[i].length == 2
// 	0 <= xi, yi <= 4 * 104
// 	All the given points are unique.
//
// Helpful references (internal KB):
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        const int N = points.size();
        unordered_map<int, unordered_set<int>> pointSet;
        for (const auto& p : points) {
            pointSet[p[0]].insert(p[1]);
        }

        int minArea = INT_MAX;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                const auto& p1 = points[i];
                const auto& p2 = points[j];
                if (p1[0] != p2[0] && p1[1] != p2[1]) {
                    if (pointSet[p1[0]].count(p2[1]) && pointSet[p2[0]].count(p1[1])) {
                        int area = abs(p1[0] - p2[0]) * abs(p1[1] - p2[1]);
                        minArea = min(minArea, area);
                    }
                }
            }
        }

        return (minArea == INT_MAX) ? 0 : minArea;          
    }
};
