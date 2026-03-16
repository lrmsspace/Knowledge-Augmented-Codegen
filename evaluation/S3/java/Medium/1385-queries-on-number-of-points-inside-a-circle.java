// Source: https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array points where points[i] = [xi, yi] is the coordinates of the ith point on a 2D plane. Multiple points can have the same coordinates.
//
// You are also given an array queries where queries[j] = [xj, yj, rj] describes a circle centered at (xj, yj) with a radius of rj.
//
// For each query queries[j], compute the number of points inside the jth circle. Points on the border of the circle are considered inside.
//
// Return an array answer, where answer[j] is the answer to the jth query.
//
// Example:
// Input: points = [[1,3],[3,3],[5,3],[2,2]], queries = [[2,3,1],[4,3,1],[1,1,2]]
// Output: [3,2,2]
// Explanation: The points and circles are shown above.
// queries[0] is the green circle, queries[1] is the red circle, and queries[2] is the blue circle.
//
// Constraints:
// 1 <= points.length <= 500
// 	points[i].length == 2
// 	0 <= x​​​​​​i, y​​​​​​i <= 500
// 	1 <= queries.length <= 500
// 	queries[j].length == 3
// 	0 <= xj, yj <= 500
// 	1 <= rj <= 500
// 	All coordinates are integers.
//
//
//  
// Follow up: Could you find the answer for each query in better complexity than O(n)?
//
// Helpful references (internal KB):
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
// - Finding common tangents to two circles (geometry, number, enumeration, simulation)
//   • When to use: When needing to find lines that are tangent to two given circles simultaneously. This method is suitable for problems requiring precise geometric line calculations.
//   • Idea: This algorithm finds common tangent lines to two circles by formulating the problem as a system of algebraic equations based on distance constraints. It involves solving a quadratic equation for line coefficients, typically resulting in constant time complexity after initial setup.
//   • Invariants: The distance from the line ax + by + c = 0 to the first circle's center is r1.; The distance from the line ax + by + c = 0 to the second circle's center is r2.
//   • Tips: Normalize the line equation (a^2 + b^2 = 1) to ensure unique representations.; Shift one circle to the origin for simpler calculations, then shift the resulting lines back.
//   • Pitfalls: Forgetting to normalize the line equation can lead to non-unique solutions.; Incorrectly handling the modulus signs (±r1, ±r2) can miss valid tangents.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] countPoints(int[][] points, int[][] queries) {
        int[] answer = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int count = 0;
            for (int[] point : points) {
                if (isInsideCircle(point, queries[i])) {
                    count++;
                }
            }
            answer[i] = count;
        }
        return answer;          
    }
}
