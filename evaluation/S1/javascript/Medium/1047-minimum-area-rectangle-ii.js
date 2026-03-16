// Source: https://leetcode.com/problems/minimum-area-rectangle-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
//
// Return the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the X and Y axes. If there is not any such rectangle, return 0.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: points = [[1,2],[2,1],[1,0],[0,1]]
// Output: 2.00000
// Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
//
// Constraints:
// 1 <= points.length <= 50
// 	points[i].length == 2
// 	0 <= xi, yi <= 4 * 104
// 	All the given points are unique.
//
// Helpful references (internal KB):
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
// - Catalan Numbers (number, counting)
//   • When to use: Use when counting arrangements of objects that follow a specific non-crossing or balancing rule, often involving recursive decomposition or paths constrained by a diagonal.
//   • Idea: Catalan numbers count the number of ways to arrange certain combinatorial objects, such as balanced parentheses sequences or monotonic paths that do not cross a diagonal. They can be computed using a recurrence relation (O(N^2) with DP) or a direct binomial coefficient formula (O(N) or O(N log N)).
//   • Invariants: dp[i] stores the i-th Catalan number, correctly computed from dp[0] through dp[i-1].; For each n, the sum sum(dp[k] * dp[n-1-k]) iterates through all valid partitions of the problem.
//   • Tips: Memoize the recursive solution to avoid redundant computations, transforming it into dynamic programming.; For large N, use modular arithmetic if results are required modulo a prime to prevent integer overflow.
//   • Pitfalls: Forgetting to correctly handle the base cases, typically C0 = 1 and C1 = 1.; Encountering integer overflow when calculating large binomial coefficients without appropriate modular arithmetic.
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
var minAreaFreeRect = function(points) {
	const pointSet = new Set();
	for (const [x, y] of points) {
		pointSet.add(`${x},${y}`);
	}

	let minArea = Infinity;

	for (let i = 0; i < points.length; i++) {
		for (let j = i + 1; j < points.length; j++) {
			const [x1, y1] = points[i];
			const [x2, y2] = points[j];

			const midX = (x1 + x2) / 2;
			const midY = (y1 + y2) / 2;

			for (let k = 0; k < points.length; k++) {
				if (k === i || k === j) continue;

				const [x3, y3] = points[k];
				const x4 = 2 * midX - x3;
				const y4 = 2 * midY - y3;

				if (pointSet.has(`${x4},${y4}`)) {
					const area = Math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2) * Math.sqrt((x3 - x1) ** 2 + (y3 - y1) ** 2);
					minArea = Math.min(minArea, area);
				}
			}
		}
	}

	return minArea === Infinity ? 0 : minArea;
};
