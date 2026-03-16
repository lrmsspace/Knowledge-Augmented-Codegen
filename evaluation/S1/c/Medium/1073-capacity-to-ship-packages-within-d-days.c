// Source: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/   |   Difficulty: Medium
//
// Problem Description:
// A conveyor belt has packages that must be shipped from one port to another within days days.
//
// The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.
//
// Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.
//
// Example:
// Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
// Output: 15
// Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
// 1st day: 1, 2, 3, 4, 5
// 2nd day: 6, 7
// 3rd day: 8
// 4th day: 9
// 5th day: 10
//
// Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.
//
// Constraints:
// 1 <= days <= weights.length <= 5 * 104
// 	1 <= weights[i] <= 500
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int shipWithinDays(int* weights, int weightsSize, int days) {
    int left = 0, right = 0;
    for (int i = 0; i < weightsSize; ++i) {
        if (weights[i] > left) {
            left = weights[i];
        }
        right += weights[i];
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        int requiredDays = 1;
        int currentLoad = 0;

        for (int i = 0; i < weightsSize; ++i) {
            if (currentLoad + weights[i] > mid) {
                ++requiredDays;
                currentLoad = 0;
            }
            currentLoad += weights[i];
        }

        if (requiredDays > days) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;        
}
