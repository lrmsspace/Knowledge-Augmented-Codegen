// Source: https://leetcode.com/problems/minimum-cost-to-reach-every-position/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array cost of size n. You are currently at position n (at the end of the line) in a line of n + 1 people (numbered from 0 to n).
//
// You wish to move forward in the line, but each person in front of you charges a specific amount to swap places. The cost to swap with person i is given by cost[i].
//
// You are allowed to swap places with people as follows:
//
//
// 	If they are in front of you, you must pay them cost[i] to swap with them.
// 	If they are behind you, they can swap with you for free.
//
//
// Return an array answer of size n, where answer[i] is the minimum total cost to reach each position i in the line.
//
// Example:
// Input: cost = [5,3,4,1,3,2]
//
// Output: [5,3,3,1,1,1]
//
// Explanation:
//
// We can get to each position in the following way:
//
//
// 	i = 0. We can swap with person 0 for a cost of 5.
// 	i = 1. We can swap with person 1 for a cost of 3.
// 	i = 2. We can swap with person 1 for a cost of 3, then swap with person 2 for free.
// 	i = 3. We can swap with person 3 for a cost of 1.
// 	i = 4. We can swap with person 3 for a cost of 1, then swap with person 4 for free.
// 	i = 5. We can swap with person 3 for a cost of 1, then swap with person 5 for free.
//
// Constraints:
// 1 <= n == cost.length <= 100
// 	1 <= cost[i] <= 100
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} cost
 * @return {number[]}
 */
var minCosts = function(cost) {
    const n = cost.length;
    const answer = new Array(n);
    
    for (let i = 0; i < n; i++) {
        answer[i] = cost[i]; // Cost to swap directly with person i
        
        for (let j = 0; j < i; j++) {
            // Cost to swap with person j and then move forward to i
            answer[i] = Math.min(answer[i], answer[j] + cost[i]);
        }
    }
    
    return answer;
};
