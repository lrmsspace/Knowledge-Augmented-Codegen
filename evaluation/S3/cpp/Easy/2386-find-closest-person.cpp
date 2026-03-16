// Source: https://leetcode.com/problems/find-closest-person/   |   Difficulty: Easy
//
// Problem Description:
// You are given three integers x, y, and z, representing the positions of three people on a number line:
//
//
// 	x is the position of Person 1.
// 	y is the position of Person 2.
// 	z is the position of Person 3, who does not move.
//
//
// Both Person 1 and Person 2 move toward Person 3 at the same speed.
//
// Determine which person reaches Person 3 first:
//
//
// 	Return 1 if Person 1 arrives first.
// 	Return 2 if Person 2 arrives first.
// 	Return 0 if both arrive at the same time.
//
//
// Return the result accordingly.
//
// Example:
// Input: x = 2, y = 7, z = 4
//
// Output: 1
//
// Explanation:
//
//
// 	Person 1 is at position 2 and can reach Person 3 (at position 4) in 2 steps.
// 	Person 2 is at position 7 and can reach Person 3 in 3 steps.
//
//
// Since Person 1 reaches Person 3 first, the output is 1.
//
// Constraints:
// 1 <= x, y, z <= 100
//
// Helpful references (internal KB):
// - Oriented area of a triangle (geometry, number, simulation)
//   • When to use: Use when determining the orientation of three 2D points (clockwise, counterclockwise, or collinear) or calculating the signed area of a triangle formed by them. It's crucial for geometric algorithms like convex hull construction and point-in-polygon tests.
//   • Idea: Calculates the signed area of a triangle defined by three 2D points, indicating their orientation relative to each other. A positive sign typically means counterclockwise, negative means clockwise, and zero indicates collinearity.
//   • Invariants: The sign of the result correctly indicates the orientation of p1, p2, p3 (e.g., positive for counter-clockwise).; If the points are collinear, the calculated oriented area is exactly zero.
//   • Tips: The sign of the result directly indicates the orientation of the points.; The absolute value of the result gives the standard unsigned area of the triangle.
//   • Pitfalls: Floating-point precision issues can lead to incorrect collinearity checks or orientation.; Inconsistent definitions of 'clockwise' vs. 'counterclockwise' can flip the sign interpretation.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Manhattan Distance (geometry, number, coordinate-compress)
//   • When to use: Use when calculating distance between two points on a grid where movement is restricted to horizontal and vertical directions. It is also useful for problems involving maximizing or minimizing sums of absolute coordinate differences, often transformable to Chebyshev distance.
//   • Idea: Manhattan distance measures the sum of absolute differences of Cartesian coordinates between two points. It can be transformed into a Chebyshev distance problem by rotating coordinates, enabling efficient O(N) max/min distance calculations.
//   • Invariants: For any two points P1=(x1, y1) and P2=(x2, y2), the Manhattan distance is always non-negative.; The transformed points P1'=(x1+y1, y1-x1) and P2'=(x2+y2, y2-x2) satisfy Chebyshev(P1', P2') == Manhattan(P1, P2).
//   • Tips: Consider transforming to Chebyshev distance for max/min distance problems.; The transformation involves rotating coordinates: (x, y) -> (x+y, y-x).
//   • Pitfalls: Confusing with Euclidean distance, which allows diagonal movement.; Incorrectly applying coordinate transformation (e.g., wrong signs).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findClosest(int x, int y, int z) {
        int dist1 = abs(x - z);
        int dist2 = abs(y - z);

        if (dist1 < dist2) {
            return 1; // Person 1 is closer
        } else if (dist2 < dist1) {
            return 2; // Person 2 is closer
        } else {
            return 0; // Both are equidistant
        }           
    }
};
