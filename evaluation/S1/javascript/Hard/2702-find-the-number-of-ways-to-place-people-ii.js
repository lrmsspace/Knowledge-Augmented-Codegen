// Source: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
//
// We define the right direction as positive x-axis (increasing x-coordinate) and the left direction as negative x-axis (decreasing x-coordinate). Similarly, we define the up direction as positive y-axis (increasing y-coordinate) and the down direction as negative y-axis (decreasing y-coordinate)
//
// You have to place n people, including Alice and Bob, at these points such that there is exactly one person at every point. Alice wants to be alone with Bob, so Alice will build a rectangular fence with Alice's position as the upper left corner and Bob's position as the lower right corner of the fence (Note that the fence might not enclose any area, i.e. it can be a line). If any person other than Alice and Bob is either inside the fence or on the fence, Alice will be sad.
//
// Return the number of pairs of points where you can place Alice and Bob, such that Alice does not become sad on building the fence.
//
// Note that Alice can only build a fence with Alice's position as the upper left corner, and Bob's position as the lower right corner. For example, Alice cannot build either of the fences in the picture below with four corners (1, 1), (1, 3), (3, 1), and (3, 3), because:
//
//
// 	With Alice at (3, 3) and Bob at (1, 1), Alice's position is not the upper left corner and Bob's position is not the lower right corner of the fence.
// 	With Alice at (1, 3) and Bob at (1, 1) (as the rectangle shown in the image instead of a line), Bob's position is not the lower right corner of the fence.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 0
// Explanation: There is no way to place Alice and Bob such that Alice can build a fence with Alice's position as the upper left corner and Bob's position as the lower right corner. Hence we return 0.
//
// Constraints:
// 2 <= n <= 1000
// 	points[i].length == 2
// 	-109 <= points[i][0], points[i][1] <= 109
// 	All points[i] are distinct.
//
// Helpful references (internal KB):
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Finding intersection of two segments (geometry, interval, simulation, interval-scheduling)
//   • When to use: When determining if two line segments in 2D space cross, touch, or overlap, and to find the nature of their intersection (point, segment, or empty).
//   • Idea: This algorithm determines if two line segments intersect and calculates their intersection point or segment. It typically involves checking for orientation changes and handling special cases like collinearity, with an O(1) time complexity.
//   • Invariants: The bounding boxes of the two segments must overlap for an intersection to be possible.; If segments are collinear, their intersection is either empty, a point, or a sub-segment.
//   • Tips: Use a bounding box check first for early exit optimization.; Handle collinear segments as a distinct special case.
//   • Pitfalls: Incorrectly handling parallel or perfectly collinear segments.; Floating point inaccuracies leading to false positives or negatives.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} points
 * @return {number}
 */
var numberOfPairs = function(points) {
	var n = points.length;
	var count = 0;

	for (var i = 0; i < n; i++) {
		for (var j = i + 1; j < n; j++) {
			var x1 = points[i][0];
			var y1 = points[i][1];
			var x2 = points[j][0];
			var y2 = points[j][1];

			if (x1 <= x2 && y1 >= y2) {
				count++;
			}
		}
	}

	return count;
};
