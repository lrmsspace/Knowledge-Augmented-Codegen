// Source: https://leetcode.com/problems/maximum-number-of-robots-within-budget/   |   Difficulty: Hard
//
// Problem Description:
// You have n robots. You are given two 0-indexed integer arrays, chargeTimes and runningCosts, both of length n. The ith robot costs chargeTimes[i] units to charge and costs runningCosts[i] units to run. You are also given an integer budget.
//
// The total cost of running k chosen robots is equal to max(chargeTimes) + k * sum(runningCosts), where max(chargeTimes) is the largest charge cost among the k robots and sum(runningCosts) is the sum of running costs among the k robots.
//
// Return the maximum number of consecutive robots you can run such that the total cost does not exceed budget.
//
// Example:
// Input: chargeTimes = [3,6,1,3,4], runningCosts = [2,1,3,4,5], budget = 25
// Output: 3
// Explanation: 
// It is possible to run all individual and consecutive pairs of robots within budget.
// To obtain answer 3, consider the first 3 robots. The total cost will be max(3,6,1) + 3 * sum(2,1,3) = 6 + 3 * 6 = 24 which is less than 25.
// It can be shown that it is not possible to run more than 3 consecutive robots within budget, so we return 3.
//
// Constraints:
// chargeTimes.length == runningCosts.length == n
// 	1 <= n <= 5 * 104
// 	1 <= chargeTimes[i], runningCosts[i] <= 105
// 	1 <= budget <= 1015
//
// Helpful references (internal KB):
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Convex hull trick and Li Chao tree (array, number, dp-1d)
//   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
//   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
//   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
//   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
//   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumRobots(int* chargeTimes, int chargeTimesSize, int* runningCosts, int runningCostsSize, long long budget) {
    int left = 0, right = 0, maxRobots = 0;
    long long runningCostSum = 0;
    int maxChargeTime = 0;

    while (right < chargeTimesSize) {
        runningCostSum += runningCosts[right];
        if (chargeTimes[right] > maxChargeTime) {
            maxChargeTime = chargeTimes[right];
        }

        while (maxChargeTime + (long long)(right - left + 1) * runningCostSum > budget) {
            runningCostSum -= runningCosts[left];
            if (chargeTimes[left] == maxChargeTime) {
                maxChargeTime = 0; // Reset and recalculate
                for (int i = left + 1; i <= right; i++) {
                    if (chargeTimes[i] > maxChargeTime) {
                        maxChargeTime = chargeTimes[i];
                    }
                }
            }
            left++;
        }

        int currentRobots = right - left + 1;
        if (currentRobots > maxRobots) {
            maxRobots = currentRobots;
        }
        right++;
    }

    return maxRobots;       
}
