// Source: https://leetcode.com/problems/largest-triangle-area/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of points on the X-Y plane points where points[i] = [xi, yi], return the area of the largest triangle that can be formed by any three different points. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
// Output: 2.00000
// Explanation: The five points are shown in the above figure. The red triangle is the largest.
//
// Constraints:
// 3 <= points.length <= 50
// 	-50 <= xi, yi <= 50
// 	All the given points are unique.
//
// Helpful references (internal KB):
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Oriented area of a triangle (geometry, number, simulation)
//   • When to use: Use when determining the orientation of three 2D points (clockwise, counterclockwise, or collinear) or calculating the signed area of a triangle formed by them. It's crucial for geometric algorithms like convex hull construction and point-in-polygon tests.
//   • Idea: Calculates the signed area of a triangle defined by three 2D points, indicating their orientation relative to each other. A positive sign typically means counterclockwise, negative means clockwise, and zero indicates collinearity.
//   • Invariants: The sign of the result correctly indicates the orientation of p1, p2, p3 (e.g., positive for counter-clockwise).; If the points are collinear, the calculated oriented area is exactly zero.
//   • Tips: The sign of the result directly indicates the orientation of the points.; The absolute value of the result gives the standard unsigned area of the triangle.
//   • Pitfalls: Floating-point precision issues can lead to incorrect collinearity checks or orientation.; Inconsistent definitions of 'clockwise' vs. 'counterclockwise' can flip the sign interpretation.
// - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
//   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
//   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
//   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
//   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
//   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double largestTriangleArea(int** points, int pointsSize, int* pointsColSize) {
    double max_area = 0.0;

    for (int i = 0; i < pointsSize - 2; i++) {
        for (int j = i + 1; j < pointsSize - 1; j++) {
            for (int k = j + 1; k < pointsSize; k++) {
                double area = 0.5 * fabs(
                    points[i][0] * (points[j][1] - points[k][1]) +
                    points[j][0] * (points[k][1] - points[i][1]) +
                    points[k][0] * (points[i][1] - points[j][1])
                );
                if (area > max_area) {
                    max_area = area;
                }
            }
        }
    }

    return max_area;        
}
