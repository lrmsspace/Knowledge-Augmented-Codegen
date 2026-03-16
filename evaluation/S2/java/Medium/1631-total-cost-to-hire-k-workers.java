// Source: https://leetcode.com/problems/total-cost-to-hire-k-workers/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.
//
// You are also given two integers k and candidates. We want to hire exactly k workers according to the following rules:
//
//
// 	You will run k sessions and hire exactly one worker in each session.
// 	In each hiring session, choose the worker with the lowest cost from either the first candidates workers or the last candidates workers. Break the tie by the smallest index.
// 	
// 		For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session, we will choose the 4th worker because they have the lowest cost [3,2,7,7,1,2].
// 		In the second hiring session, we will choose 1st worker because they have the same lowest cost as 4th worker but they have the smallest index [3,2,7,7,2]. Please note that the indexing may be changed in the process.
// 	
// 	
// 	If there are fewer than candidates workers remaining, choose the worker with the lowest cost among them. Break the tie by the smallest index.
// 	A worker can only be chosen once.
//
//
// Return the total cost to hire exactly k workers.
//
// Example:
// Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
// Output: 11
// Explanation: We hire 3 workers in total. The total cost is initially 0.
// - In the first hiring round we choose the worker from [17,12,10,2,7,2,11,20,8]. The lowest cost is 2, and we break the tie by the smallest index, which is 3. The total cost = 0 + 2 = 2.
// - In the second hiring round we choose the worker from [17,12,10,7,2,11,20,8]. The lowest cost is 2 (index 4). The total cost = 2 + 2 = 4.
// - In the third hiring round we choose the worker from [17,12,10,7,11,20,8]. The lowest cost is 7 (index 3). The total cost = 4 + 7 = 11. Notice that the worker with index 3 was common in the first and last four workers.
// The total hiring cost is 11.
//
// Constraints:
// 1 <= costs.length <= 105 
// 	1 <= costs[i] <= 105
// 	1 <= k, candidates <= costs.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long totalCost(int[] costs, int k, int candidates) {
        int n = costs.length;
        long totalCost = 0;

        // Two pointers to track the candidates from the front and back
        int left = 0, right = n - 1;

        // Min-heaps to store the candidates from the front and back
        PriorityQueue<Integer> frontHeap = new PriorityQueue<>((a, b) -> costs[a] != costs[b] ? Integer.compare(costs[a], costs[b]) : Integer.compare(a, b));
        PriorityQueue<Integer> backHeap = new PriorityQueue<>((a, b) -> costs[a] != costs[b] ? Integer.compare(costs[a], costs[b]) : Integer.compare(a, b));

        // Add initial candidates to the heaps
        for (int i = 0; i < candidates && left <= right; i++) {
            frontHeap.offer(left++);
            if (left <= right) {
                backHeap.offer(right--);
            }
        }

        // Hire k workers
        for (int i = 0; i < k; i++) {
            if (frontHeap.isEmpty()) {
                totalCost += costs[backHeap.poll()];
                if (right >= left) {
                    backHeap.offer(right--);
                }
            } else if (backHeap.isEmpty()) {
                totalCost += costs[frontHeap.poll()];
                if (left <= right) {
                    frontHeap.offer(left++);
                }
            } else {
                if (costs[frontHeap.peek()] < costs[backHeap.peek()] || (costs[frontHeap.peek()] == costs[backHeap.peek()] && frontHeap.peek() < backHeap.peek())) {
                    totalCost += costs[frontHeap.poll()];
                    if (left <= right) {
                        frontHeap.offer(left++);
                    }
                } else {
                    totalCost += costs[backHeap.poll()];
                    if (right >= left) {
                        backHeap.offer(right--);
                    }
                }
            }
        }

        return totalCost;           
    }
}
