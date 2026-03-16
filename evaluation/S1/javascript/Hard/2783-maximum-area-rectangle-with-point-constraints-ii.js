// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n points on an infinite plane. You are given two integer arrays xCoord and yCoord where (xCoord[i], yCoord[i]) represents the coordinates of the ith point.
//
// Your task is to find the maximum area of a rectangle that:
//
//
// 	Can be formed using four of these points as its corners.
// 	Does not contain any other point inside or on its border.
// 	Has its edges parallel to the axes.
//
//
// Return the maximum area that you can obtain or -1 if no such rectangle is possible.
//
// Example:
// Input: xCoord = [1,1,3,3], yCoord = [1,3,1,3]
//
// Output: 4
//
// Explanation:
//
//
//
// We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
//
// Constraints:
// 1 <= xCoord.length == yCoord.length <= 2 * 105
// 	0 <= xCoord[i], yCoord[i] <= 8 * 107
// 	All the given points are unique.
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Point location in O(logn) (geometry, ds, simulation)
//   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
//   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
//   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
//   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
//   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
// - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
//   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
//   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
//   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
//   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
//   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} xCoord
 * @param {number[]} yCoord
 * @return {number}
 */
var maxRectangleArea = function(xCoord, yCoord) {
	const n = xCoord.length;
	if (n < 4) {
		return -1;
	}

	const xMap = new Map();
	const allY = new Set();
	for (let i = 0; i < n; i++) {
		const x = xCoord[i];
		const y = yCoord[i];
		if (!xMap.has(x)) {
			xMap.set(x, []);
		}
		xMap.get(x).push(y);
		allY.add(y);
	}

	const ys = Array.from(allY);
	ys.sort((a, b) => a - b);
	const yIndex = new Map();
	for (let i = 0; i < ys.length; i++) {
		yIndex.set(ys[i], i);
	}

	const xs = Array.from(xMap.keys());
	xs.sort((a, b) => a - b);

	class SegTree {
		constructor(size) {
			let n = 1;
			while (n < size) n <<= 1;
			this.size = n;
			this.data = new Array(n * 2).fill(-1);
		}

		update(pos, value) {
			let idx = pos + this.size;
			this.data[idx] = value;
			idx >>= 1;
			while (idx > 0) {
				this.data[idx] = Math.max(this.data[idx * 2], this.data[idx * 2 + 1]);
				idx >>= 1;
			}
		}

		rangeMax(left, right) {
			let l = left + this.size;
			let r = right + this.size;
			let res = -1;
			while (l <= r) {
				if ((l & 1) === 1) res = Math.max(res, this.data[l++]);
				if ((r & 1) === 0) res = Math.max(res, this.data[r--]);
				l >>= 1;
				r >>= 1;
			}
			return res;
		}
	}

	const segTree = new SegTree(ys.length);
	const pairLastX = new Map();
	let maxArea = -1;

	for (const x of xs) {
		const yList = xMap.get(x);
		yList.sort((a, b) => a - b);

		for (let i = 0; i + 1 < yList.length; i++) {
			const y1 = yList[i];
			const y2 = yList[i + 1];
			const key = y1 + "#" + y2;

			if (pairLastX.has(key)) {
				const lastX = pairLastX.get(key);
				const idx1 = yIndex.get(y1);
				const idx2 = yIndex.get(y2);
				if (segTree.rangeMax(idx1, idx2) === lastX) {
					const area = (x - lastX) * (y2 - y1);
					if (area > maxArea) maxArea = area;
				}
			}

			pairLastX.set(key, x);
		}

		for (const y of yList) {
			segTree.update(yIndex.get(y), x);
		}
	}

	return maxArea;
};
