// Source: https://leetcode.com/problems/merge-operations-for-minimum-travel-time/   |   Difficulty: Hard
//
// Problem Description:
// You are given a straight road of length l km, an integer n, an integer k, and two integer arrays, position and time, each of length n.
//
// The array position lists the positions (in km) of signs in strictly increasing order (with position[0] = 0 and position[n - 1] = l).
//
// Each time[i] represents the time (in minutes) required to travel 1 km between position[i] and position[i + 1].
//
// You must perform exactly k merge operations. In one merge, you can choose any two adjacent signs at indices i and i + 1 (with i > 0 and i + 1 < n) and:
//
//
//  Update the sign at index i + 1 so that its time becomes time[i] + time[i + 1].
//  Remove the sign at index i.
//
//
// Return the minimum total travel time (in minutes) to travel from 0 to l after exactly k merges.
//
// Example:
// Input: l = 10, n = 4, k = 1, position = [0,3,8,10], time = [5,8,3,6]
//
// Output: 62
//
// Explanation:
//
//
//  
//  Merge the signs at indices 1 and 2. Remove the sign at index 1, and change the time at index 2 to 8 + 3 = 11.
//  
//  After the merge:
//  
//   position array: [0, 8, 10]
//   time array: [5, 11, 6]
//    
//  
//  
//  
//  
//   
//    
//     Segment
//     Distance (km)
//     Time per km (min)
//     Segment Travel Time (min)
//    
//   
//   
//    
//     0 → 8
//     8
//     5
//     8 × 5 = 40
//    
//    
//     8 → 10
//     2
//     11
//     2 × 11 = 22
//    
//   
//  
//  
//  Total Travel Time: 40 + 22 = 62, which is the minimum possible time after exactly 1 merge.
//
// Constraints:
// 1 <= l <= 105
//  2 <= n <= min(l + 1, 50)
//  0 <= k <= min(n - 2, 10)
//  position.length == n
//  position[0] = 0 and position[n - 1] = l
//  position is sorted in strictly increasing order.
//  time.length == n
//  1 <= time[i] <= 100​
//  1 <= sum(time) <= 100​​​​​​
//
// Helpful references (internal KB):
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} l
 * @param {number} n
 * @param {number} k
 * @param {number[]} position
 * @param {number[]} time
 * @return {number}
 */
var minTravelTime = function(l, n, k, position, time) {
	const prefixTime = Array(n).fill(0);
	prefixTime[0] = time[0];
	for (let i = 1; i < n; i++) {
		prefixTime[i] = prefixTime[i - 1] + time[i];
	}

	const INF = Number.POSITIVE_INFINITY;
	const dp = Array.from({ length: n }, () =>
		Array.from({ length: n }, () => Array(k + 1).fill(INF))
	);

	for (let cur = 1; cur < n; cur++) {
		const merges = cur - 1;
		if (merges <= k) {
			dp[0][cur][merges] = (position[cur] - position[0]) * time[0];
		}
	}

	for (let prev = 0; prev < n - 1; prev++) {
		for (let cur = prev + 1; cur < n; cur++) {
			if (cur === n - 1) {
				continue;
			}
			const sumTimeCur = prefixTime[cur] - prefixTime[prev];
			for (let merges = 0; merges <= k; merges++) {
				const curCost = dp[prev][cur][merges];
				if (curCost === INF) {
					continue;
				}
				for (let next = cur + 1; next < n; next++) {
					const mergesAdded = next - cur - 1;
					const nextMerges = merges + mergesAdded;
					if (nextMerges > k) {
						continue;
					}
					const travel = (position[next] - position[cur]) * sumTimeCur;
					const nextCost = curCost + travel;
					if (nextCost < dp[cur][next][nextMerges]) {
						dp[cur][next][nextMerges] = nextCost;
					}
				}
			}
		}
	}

	let best = INF;
	for (let prev = 0; prev < n - 1; prev++) {
		if (dp[prev][n - 1][k] < best) {
			best = dp[prev][n - 1][k];
		}
	}

	return best;
};
