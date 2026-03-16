// Source: https://leetcode.com/problems/maximum-number-of-alloys/   |   Difficulty: Medium
//
// Problem Description:
// You are the owner of a company that creates alloys using various types of metals. There are n different types of metals available, and you have access to k machines that can be used to create alloys. Each machine requires a specific amount of each metal type to create an alloy.
//
// For the ith machine to create an alloy, it needs composition[i][j] units of metal of type j. Initially, you have stock[i] units of metal type i, and purchasing one unit of metal type i costs cost[i] coins.
//
// Given integers n, k, budget, a 1-indexed 2D array composition, and 1-indexed arrays stock and cost, your goal is to maximize the number of alloys the company can create while staying within the budget of budget coins.
//
// All alloys must be created with the same machine.
//
// Return the maximum number of alloys that the company can create.
//
// Example:
// Input: n = 3, k = 2, budget = 15, composition = [[1,1,1],[1,1,10]], stock = [0,0,0], cost = [1,2,3]
// Output: 2
// Explanation: It is optimal to use the 1st machine to create alloys.
// To create 2 alloys we need to buy the:
// - 2 units of metal of the 1st type.
// - 2 units of metal of the 2nd type.
// - 2 units of metal of the 3rd type.
// In total, we need 2 * 1 + 2 * 2 + 2 * 3 = 12 coins, which is smaller than or equal to budget = 15.
// Notice that we have 0 units of metal of each type and we have to buy all the required units of metal.
// It can be proven that we can create at most 2 alloys.
//
// Constraints:
// 1 <= n, k <= 100
// 	0 <= budget <= 108
// 	composition.length == k
// 	composition[i].length == n
// 	1 <= composition[i][j] <= 100
// 	stock.length == cost.length == n
// 	0 <= stock[i] <= 108
// 	1 <= cost[i] <= 100
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxNumberOfAlloys(int n, int k, int budget, List<List<Integer>> composition, List<Integer> stock, List<Integer> cost) {
        int left = 0, right = (int) 1e9, answer = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (canMakeAlloys(n, k, budget, composition, stock, cost, mid)) {
                answer = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return answer;          
    }
}
