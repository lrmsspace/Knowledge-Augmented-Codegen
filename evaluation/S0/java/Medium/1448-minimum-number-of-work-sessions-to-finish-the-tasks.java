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

class Solution {
    public int minSessions(int[] tasks, int sessionTime) {
        int n = tasks.length;
        int fullMask = (1 << n) - 1;

        // Precompute the time required for each subset of tasks
        int[] subsetTime = new int[1 << n];
        for (int mask = 0; mask <= fullMask; mask++) {
            int time = 0;
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) {
                    time += tasks[i];
                }
            }
            subsetTime[mask] = time;
        }

        // DP array to store the minimum sessions needed for each subset of tasks
        int[] dp = new int[1 << n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        // Fill the DP array
        for (int mask = 1; mask <= fullMask; mask++) {
            for (int subMask = mask; subMask > 0; subMask = (subMask - 1) & mask) {
                if (subsetTime[subMask] <= sessionTime) {
                    dp[mask] = Math.min(dp[mask], dp[mask ^ subMask] + 1);
                }
            }
        }

        return dp[fullMask];            
    }
}
