// Source: https://leetcode.com/problems/check-if-it-is-a-straight-line/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.
//
// Example:
// Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
// Output: true
//
// Constraints:
// 2 <= coordinates.length <= 1000
// 	coordinates[i].length == 2
// 	-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
// 	coordinates contains no duplicate point.
//
// Helpful references (internal KB):
// - Basic Geometry (geometry, matrix, number, simulation)
//   • When to use: Use when solving problems involving fundamental geometric entities like points, lines, and planes, or when performing basic vector operations to determine relationships or intersections.
//   • Idea: This card covers foundational concepts in 2D and 3D geometry, including vector products and their applications in defining lines, planes, and calculating orientations or intersections. It primarily involves algebraic manipulation of vector equations, typically with O(1) complexity for basic operations on fixed-dimension vectors.
//   • Invariants: Vector operations (cross, triple products) maintain their geometric and algebraic properties.; A line defined by two points or a point and direction vector remains consistent.
//   • Tips: Understand the geometric interpretation of vector products.; Use vector equations to define lines and planes concisely.
//   • Pitfalls: Confusing pseudo-scalar product with dot product.; Incorrectly applying cross product in 2D contexts.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean checkStraightLine(int[][] coordinates) {
        int n = coordinates.length;
        int x0 = coordinates[0][0], y0 = coordinates[0][1];
        int x1 = coordinates[1][0], y1 = coordinates[1][1];

        for (int i = 2; i < n; i++) {
            int x2 = coordinates[i][0], y2 = coordinates[i][1];
            if ((y2 - y0) * (x1 - x0) != (y1 - y0) * (x2 - x0)) {
                return false;
            }
        }

        return true;            
    }
}
