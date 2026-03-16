// Source: https://leetcode.com/problems/circle-and-rectangle-overlapping/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circle represented as (radius, xCenter, yCenter) and an axis-aligned rectangle represented as (x1, y1, x2, y2), where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the rectangle.
//
// Return true if the circle and rectangle are overlapped otherwise return false. In other words, check if there is any point (xi, yi) that belongs to the circle and the rectangle at the same time.
//
// Example:
// Input: radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
// Output: true
// Explanation: Circle and rectangle share the point (1,0).
//
// Constraints:
// 1 <= radius <= 2000
// 	-104 <= xCenter, yCenter <= 104
// 	-104 <= x1 < x2 <= 104
// 	-104 <= y1 < y2 <= 104
//
// Helpful references (internal KB):
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Circle-Line Intersection (geometry, number, enumeration, simulation)
//   • When to use: Use this algorithm to find the intersection points between a circle and a line, especially when numerical stability is a concern. It efficiently determines zero, one, or two intersection points.
//   • Idea: This algorithm finds the intersection points of a circle and a line by using geometric properties like distances and vectors, avoiding direct algebraic system solving. It determines zero, one, or two intersection points in constant time, O(1).
//   • Invariants: The distance from the origin to the line, d0, is always correctly calculated as |C| / sqrt(A^2 + B^2).; The point (x0, y0) is always the closest point on the line Ax+By+C=0 to the origin (0,0).
//   • Tips: Translate the circle to the origin for simplified calculations, adjusting the line equation accordingly.; Use the distance from the origin to the line to quickly determine the number of intersection points.
//   • Pitfalls: Floating point precision errors can accumulate, especially with very small or large coordinates.; Incorrectly handling edge cases where the line is tangent to the circle or passes through the origin.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
    // Find the closest point on the rectangle to the circle's center
    int closestX = (xCenter < x1) ? x1 : (xCenter > x2) ? x2 : xCenter;
    int closestY = (yCenter < y1) ? y1 : (yCenter > y2) ? y2 : yCenter;

    // Calculate the distance from the circle's center to this closest point
    int dx = closestX - xCenter;
    int dy = closestY - yCenter;

    // Check if the distance is less than or equal to the radius
    return dx * dx + dy * dy <= radius * radius;        
}
