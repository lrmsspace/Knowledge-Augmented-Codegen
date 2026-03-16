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
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        if (n <= 2) return true;

        int x0 = coordinates[0][0];
        int y0 = coordinates[0][1];
        int x1 = coordinates[1][0];
        int y1 = coordinates[1][1];

        int dx = x1 - x0;
        int dy = y1 - y0;

        for (int i = 2; i < n; ++i) {
            int xi = coordinates[i][0];
            int yi = coordinates[i][1];

            // Check if the cross product (dx, dy) x (xi - x0, yi - y0) is zero
            if (dy * (xi - x0) != dx * (yi - y0)) {
                return false;
            }
        }

        return true;            
    }
};
