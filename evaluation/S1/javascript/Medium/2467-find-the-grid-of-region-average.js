// Source: https://leetcode.com/problems/find-the-grid-of-region-average/   |   Difficulty: Medium
//
// Problem Description:
// You are given m x n grid image which represents a grayscale image, where image[i][j] represents a pixel with intensity in the range [0..255]. You are also given a non-negative integer threshold.
//
// Two pixels are adjacent if they share an edge.
//
// A region is a 3 x 3 subgrid where the absolute difference in intensity between any two adjacent pixels is less than or equal to threshold.
//
// All pixels in a region belong to that region, note that a pixel can belong to multiple regions.
//
// You need to calculate a m x n grid result, where result[i][j] is the average intensity of the regions to which image[i][j] belongs, rounded down to the nearest integer. If image[i][j] belongs to multiple regions, result[i][j] is the average of the rounded-down average intensities of these regions, rounded down to the nearest integer. If image[i][j] does not belong to any region, result[i][j] is equal to image[i][j].
//
// Return the grid result.
//
// Example:
// Input: image = [[5,6,7,10],[8,9,10,10],[11,12,13,10]], threshold = 3
//
// Output: [[9,9,9,9],[9,9,9,9],[9,9,9,9]]
//
// Explanation:
//
//
//
// There are two regions as illustrated above. The average intensity of the first region is 9, while the average intensity of the second region is 9.67 which is rounded down to 9. The average intensity of both of the regions is (9 + 9) / 2 = 9. As all the pixels belong to either region 1, region 2, or both of them, the intensity of every pixel in the result is 9.
//
// Please note that the rounded-down values are used when calculating the average of multiple regions, hence the calculation is done using 9 as the average intensity of region 2, not 9.67.
//
// Constraints:
// 3 <= n, m <= 500
// 	0 <= image[i][j] <= 255
// 	0 <= threshold <= 255
//
// Helpful references (internal KB):
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} image
 * @param {number} threshold
 * @return {number[][]}
 */
var resultGrid = function(image, threshold) {
	var m = image.length;
	var n = image[0].length;

	var avgSum = Array.from({ length: m }, function() {
		return Array(n).fill(0);
	});
	var avgCount = Array.from({ length: m }, function() {
		return Array(n).fill(0);
	});

	for (var i = 0; i + 2 < m; i++) {
		for (var j = 0; j + 2 < n; j++) {
			var valid = true;

			for (var r = i; r <= i + 2 && valid; r++) {
				for (var c = j; c <= j + 1; c++) {
					if (Math.abs(image[r][c] - image[r][c + 1]) > threshold) {
						valid = false;
						break;
					}
				}
			}

			for (var r2 = i; r2 <= i + 1 && valid; r2++) {
				for (var c2 = j; c2 <= j + 2; c2++) {
					if (Math.abs(image[r2][c2] - image[r2 + 1][c2]) > threshold) {
						valid = false;
						break;
					}
				}
			}

			if (!valid) {
				continue;
			}

			var sum = 0;
			for (var r3 = i; r3 <= i + 2; r3++) {
				for (var c3 = j; c3 <= j + 2; c3++) {
					sum += image[r3][c3];
				}
			}
			var avg = Math.floor(sum / 9);

			for (var r4 = i; r4 <= i + 2; r4++) {
				for (var c4 = j; c4 <= j + 2; c4++) {
					avgSum[r4][c4] += avg;
					avgCount[r4][c4] += 1;
				}
			}
		}
	}

	var result = Array.from({ length: m }, function() {
		return Array(n).fill(0);
	});

	for (var r5 = 0; r5 < m; r5++) {
		for (var c5 = 0; c5 < n; c5++) {
			if (avgCount[r5][c5] === 0) {
				result[r5][c5] = image[r5][c5];
			} else {
				result[r5][c5] = Math.floor(avgSum[r5][c5] / avgCount[r5][c5]);
			}
		}
	}

	return result;
};
