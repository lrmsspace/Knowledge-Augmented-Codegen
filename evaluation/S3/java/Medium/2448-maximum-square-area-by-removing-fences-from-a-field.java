// Source: https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/   |   Difficulty: Medium
//
// Problem Description:
// There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.
//
// Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).
//
// Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.
//
// Example:
// Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
// Output: 4
// Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.
//
// Constraints:
// 3 <= m, n <= 109
// 	1 <= hFences.length, vFences.length <= 600
// 	1 < hFences[i] < m
// 	1 < vFences[i] < n
// 	hFences and vFences are unique.
//
// Helpful references (internal KB):
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximizeSquareArea(int m, int n, int[] hFences, int[] vFences) {
        int mod = 1_000_000_007;

        // Include the boundaries of the field as fences
        int[] horizontal = new int[hFences.length + 2];
        int[] vertical = new int[vFences.length + 2];

        horizontal[0] = 1; // Top boundary
        vertical[0] = 1;   // Left boundary

        for (int i = 0; i < hFences.length; i++) {
            horizontal[i + 1] = hFences[i];
        }
        for (int i = 0; i < vFences.length; i++) {
            vertical[i + 1] = vFences[i];
        }

        horizontal[horizontal.length - 1] = m; // Bottom boundary
        vertical[vertical.length - 1] = n;     // Right boundary

        Arrays.sort(horizontal);
        Arrays.sort(vertical);

        // Find the maximum gap between consecutive horizontal fences
        int maxHorizontalGap = 0;
        for (int i = 1; i < horizontal.length; i++) {
            maxHorizontalGap = Math.max(maxHorizontalGap, horizontal[i] - horizontal[i - 1]);
        }

        // Find the maximum gap between consecutive vertical fences
        int maxVerticalGap = 0;
        for (int i = 1; i < vertical.length; i++) {
            maxVerticalGap = Math.max(maxVerticalGap, vertical[i] - vertical[i - 1]);
        }

        // The largest square area is the minimum of the two maximum gaps squared
        long maxSquareArea = (long) Math.min(maxHorizontalGap, maxVerticalGap) * Math.min(maxHorizontalGap, maxVerticalGap);
        
        return (int) (maxSquareArea % mod);         
    }
}
