// Source: https://leetcode.com/problems/valid-square/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.
//
// The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.
//
// A valid square has four equal sides with positive length and four equal angles (90-degree angles).
//
// Example:
// Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
// Output: true
//
// Constraints:
// p1.length == p2.length == p3.length == p4.length == 2
// 	-104 <= xi, yi <= 104
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Finding common tangents to two circles (geometry, number, enumeration, simulation)
//   • When to use: Use this when you need to find all lines that are simultaneously tangent to two given circles. It is applicable in computational geometry problems requiring the precise relative positioning of circles and lines.
//   • Idea: This algorithm systematically determines the equations of all common tangent lines to two circles, typically identifying up to four distinct lines. It involves geometric calculations based on circle centers and radii, operating in constant time, O(1).
//   • Invariants: The distance between the two circle centers remains constant.; The radii of both circles are immutable during the tangent calculation.
//   • Tips: Separate calculations for external and internal tangents.; Carefully consider the relative positions of circle centers and radii.
//   • Pitfalls: Overlooking degenerate cases like coincident or concentric circles.; Numerical instability or precision errors with floating-point arithmetic.
// - Finding common tangents to two circles (geometry, number, enumeration, simulation)
//   • When to use: When needing to find lines that are tangent to two given circles simultaneously. This method is suitable for problems requiring precise geometric line calculations.
//   • Idea: This algorithm finds common tangent lines to two circles by formulating the problem as a system of algebraic equations based on distance constraints. It involves solving a quadratic equation for line coefficients, typically resulting in constant time complexity after initial setup.
//   • Invariants: The distance from the line ax + by + c = 0 to the first circle's center is r1.; The distance from the line ax + by + c = 0 to the second circle's center is r2.
//   • Tips: Normalize the line equation (a^2 + b^2 = 1) to ensure unique representations.; Shift one circle to the origin for simpler calculations, then shift the resulting lines back.
//   • Pitfalls: Forgetting to normalize the line equation can lead to non-unique solutions.; Incorrectly handling the modulus signs (±r1, ±r2) can miss valid tangents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool validSquare(int* p1, int p1Size, int* p2, int p2Size, int* p3, int p3Size, int* p4, int p4Size) {
    int points[4][2] = { {p1[0], p1[1]}, {p2[0], p2[1]}, {p3[0], p3[1]}, {p4[0], p4[1]} };
    int dists[6];
    int idx = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int dx = points[i][0] - points[j][0];
            int dy = points[i][1] - points[j][1];
            dists[idx++] = dx * dx + dy * dy;
        }
    }
    
    // Sort distances
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            if (dists[j] > dists[j + 1]) {
                int temp = dists[j];
                dists[j] = dists[j + 1];
                dists[j + 1] = temp;
            }
        }
    }
    
    // Check the square condition
    return dists[0] > 0 && 
           dists[0] == dists[1] && 
           dists[0] == dists[2] && 
           dists[0] == dists[3] && 
           dists[4] == dists[5] && 
           dists[4] == 2 * dists[0];  
                 
}
