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
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
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
        int n = tasks.size(), m = 1 << n;
        vector<int> dp(m, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < m; ++i) {
            if (dp[i] == INT_MAX) continue;
            int sum = 0;
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) sum += tasks[j];
            }
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) continue;
                if (sum + tasks[j] <= sessionTime) {
                    dp[i | (1 << j)] = min(dp[i | (1 << j)], dp[i]);
                } else {
                    dp[i | (1 << j)] = min(dp[i | (1 << j)], dp[i] + 1);
                }
            }
        }
        return dp[m - 1] + 1;           
    }
};
