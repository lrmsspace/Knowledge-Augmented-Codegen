// Source: https://leetcode.com/problems/find-maximum-area-of-a-triangle/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array coords of size n x 2, representing the coordinates of n points in an infinite Cartesian plane.
//
// Find twice the maximum area of a triangle with its corners at any three elements from coords, such that at least one side of this triangle is parallel to the x-axis or y-axis. Formally, if the maximum area of such a triangle is A, return 2 * A.
//
// If no such triangle exists, return -1.
//
// Note that a triangle cannot have zero area.
//
// Example:
// Input: coords = [[1,1],[1,2],[3,2],[3,3]]
//
// Output: 2
//
// Explanation:
//
//
//
// The triangle shown in the image has a base 1 and height 2. Hence its area is 1/2 * base * height = 1.
//
// Constraints:
// 1 <= n == coords.length <= 105
// 	1 <= coords[i][0], coords[i][1] <= 106
// 	All coords[i] are unique.
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maxArea(vector<vector<int>>& coords) {
        long long max_area = -1;
        unordered_map<int, vector<int>> x_to_ys, y_to_xs;

        for (const auto& coord : coords) {
            int x = coord[0], y = coord[1];
            x_to_ys[x].push_back(y);
            y_to_xs[y].push_back(x);
        }

        for (const auto& [x, ys] : x_to_ys) {
            for (size_t i = 0; i < ys.size(); ++i) {
                for (size_t j = i + 1; j < ys.size(); ++j) {
                    int y1 = ys[i], y2 = ys[j];
                    int height = abs(y2 - y1);

                    for (int x2 : y_to_xs[y1]) {
                        if (x2 != x) {
                            max_area = max(max_area, static_cast<long long>(height) * abs(x2 - x));
                        }
                    }

                    for (int x2 : y_to_xs[y2]) {
                        if (x2 != x) {
                            max_area = max(max_area, static_cast<long long>(height) * abs(x2 - x));
                        }
                    }
                }
            }
        }

        return max_area;            
    }
};
