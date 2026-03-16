// Source: https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/   |   Difficulty: Hard
//
// Problem Description:
// Alice is throwing n darts on a very large wall. You are given an array darts where darts[i] = [xi, yi] is the position of the ith dart that Alice threw on the wall.
//
// Bob knows the positions of the n darts on the wall. He wants to place a dartboard of radius r on the wall so that the maximum number of darts that Alice throws lie on the dartboard.
//
// Given the integer r, return the maximum number of darts that can lie on the dartboard.
//
// Example:
// Input: darts = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
// Output: 4
// Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
//
// Constraints:
// 1 <= darts.length <= 100
// 	darts[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the darts are unique
// 	1 <= r <= 5000
//
// Helpful references (internal KB):
// - Finding common tangents to two circles (geometry, number, enumeration, simulation)
//   • When to use: Use this when you need to find all lines that are simultaneously tangent to two given circles. It is applicable in computational geometry problems requiring the precise relative positioning of circles and lines.
//   • Idea: This algorithm systematically determines the equations of all common tangent lines to two circles, typically identifying up to four distinct lines. It involves geometric calculations based on circle centers and radii, operating in constant time, O(1).
//   • Invariants: The distance between the two circle centers remains constant.; The radii of both circles are immutable during the tangent calculation.
//   • Tips: Separate calculations for external and internal tangents.; Carefully consider the relative positions of circle centers and radii.
//   • Pitfalls: Overlooking degenerate cases like coincident or concentric circles.; Numerical instability or precision errors with floating-point arithmetic.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numPoints(int** darts, int dartsSize, int* dartsColSize, int r) {
    // This problem can be solved using a geometric approach. The idea is to find the center of the circle that can contain the maximum number of darts. We can do this by considering each pair of darts and calculating the possible centers of circles with radius r that can pass through both darts.

    // We will iterate through each pair of darts and calculate the centers of the circles that can pass through them. For each center, we will count how many darts lie within or on the boundary of the circle.

    int maxDarts = 1; // At least one dart can be on the dartboard

    for (int i = 0; i < dartsSize; i++) {
        for (int j = i + 1; j < dartsSize; j++) {
            // Get the coordinates of the two darts
            int x1 = darts[i][0], y1 = darts[i][1];
            int x2 = darts[j][0], y2 = darts[j][1];

            // Calculate the distance between the two darts
            double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

            // If the distance is greater than 2*r, they cannot be on the same circle
            if (dist > 2 * r) {
                continue;
            }

            // Calculate the midpoint between the two darts
            double midX = (x1 + x2) / 2.0;
            double midY = (y1 + y2) / 2.0;

            // Calculate the distance from the midpoint to the center of the circle
            double h = sqrt(r * r - (dist / 2) * (dist / 2));

            // Calculate the direction vector from dart i to dart j
            double dirX = (y2 - y1) / dist;
            double dirY = (x1 - x2) / dist;

            // Calculate the two possible centers of the circles
            double centerX1 = midX + h * dirX;
            double centerY1 = midY + h * dirY;
            double centerX2 = midX - h * dirX;
            double centerY2 = midY - h * dirY;

            // Count how many darts are within or on the boundary of the first circle
            int count1 = 0;
            for (int k = 0; k < dartsSize; k++) {
                double d = sqrt((darts[k][0] - centerX1) * (darts[k][0] - centerX1) + (darts[k][1] - centerY1) * (darts[k][1] - centerY1));
                if (d <= r) {
                    count1++;
                }
            }
            if (count1 > maxDarts) {
                maxDarts = count1;
            }
            
            // Count how many darts are within or on the boundary of the second circle
            int count2 = 0;
            for (int k = 0; k < dartsSize; k++) {
                double d = sqrt((darts[k][0] - centerX2) * (darts[k][0] - centerX2) + (darts[k][1] - centerY2) * (darts[k][1] - centerY2));
                if (d <= r) {
                    count2++;
                }
            }
            if (count2 > maxDarts) {
                maxDarts = count2;
            }
        }
    }
    return maxDarts;
}