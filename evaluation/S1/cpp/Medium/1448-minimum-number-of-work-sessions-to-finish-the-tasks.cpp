// Source: https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/   |   Difficulty: Medium
//
// Problem Description:
// There are n tasks assigned to you. The task times are represented as an integer array tasks of length n, where the ith task takes tasks[i] hours to finish. A work session is when you work for at most sessionTime consecutive hours and then take a break.
//
// You should finish the given tasks in a way that satisfies the following conditions:
//
//
// 	If you start a task in a work session, you must complete it in the same work session.
// 	You can start a new task immediately after finishing the previous one.
// 	You may complete the tasks in any order.
//
//
// Given tasks and sessionTime, return the minimum number of work sessions needed to finish all the tasks following the conditions above.
//
// The tests are generated such that sessionTime is greater than or equal to the maximum element in tasks[i].
//
// Example:
// Input: tasks = [1,2,3], sessionTime = 3
// Output: 2
// Explanation: You can finish the tasks in two work sessions.
// - First work session: finish the first and the second tasks in 1 + 2 = 3 hours.
// - Second work session: finish the third task in 3 hours.
//
// Constraints:
// n == tasks.length
// 	1 <= n <= 14
// 	1 <= tasks[i] <= 10
// 	max(tasks[i]) <= sessionTime <= 15
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        int totalMasks = 1 << n;
        std::vector<int> sessionCost(totalMasks, 0);

        // Precompute the session cost for each subset of tasks
        for (int mask = 0; mask < totalMasks; ++mask) {
            int timeSum = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    timeSum += tasks[i];
                }
            }
            sessionCost[mask] = (timeSum <= sessionTime) ? timeSum : sessionTime + 1;
        }

        std::vector<int> dp(totalMasks, n + 1);
        dp[0] = 0;

        // Dynamic programming to find the minimum number of sessions
        for (int mask = 1; mask < totalMasks; ++mask) {
            for (int submask = mask; submask; submask = (submask - 1) & mask) {
                if (sessionCost[submask] <= sessionTime) {
                    dp[mask] = std::min(dp[mask], dp[mask ^ submask] + 1);
                }
            }
        }

        return dp[totalMasks - 1];          
    }
};
