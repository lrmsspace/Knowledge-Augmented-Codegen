// Source: https://leetcode.com/problems/separate-squares-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted multiple times.
//
// Example:
// Input: squares = [[0,0,1],[2,2,1]]
//
// Output: 1.00000
//
// Explanation:
//
//
//
// Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it. The lowest option is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1012.
//
// Helpful references (internal KB):
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    // Helper function to calculate area above a given line y = lineY
    long long areaAboveLine(int** squares, int squaresSize, double lineY) {
        long long area = 0;
        for (int i = 0; i < squaresSize; i++) {
            int x = squares[i][0];
            int y = squares[i][1];
            int l = squares[i][2];
            if (y + l <= lineY) {
                continue; // Entire square is below the line
            } else if (y >= lineY) {
                area += (long long)l * l; // Entire square is above the line
            } else {
                double heightAbove = (y + l) - lineY;
                area += (long long)l * heightAbove; // Partial area above the line
            }
        }
        return area;
    }

    // Binary search to find the correct y-coordinate
    double low = 0.0, high = 1e9 + 1e9; // Based on constraints
    for (int iter = 0; iter < 100; iter++) { // 100 iterations for precision
        double mid = (low + high) / 2.0;
        long long areaAbove = areaAboveLine(squares, squaresSize, mid);
        long long totalArea = 0;
        for (int i = 0; i < squaresSize; i++) {
            totalArea += (long long)squares[i][2] * squares[i][2];
        }
        if (areaAbove * 2 < totalArea) {
            low = mid; // Need more area above
        } else {
            high = mid; // Too much area above
        }
    }
    return (low + high) / 2.0;
}
