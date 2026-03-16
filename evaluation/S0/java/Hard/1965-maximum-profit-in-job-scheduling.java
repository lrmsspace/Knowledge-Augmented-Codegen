// Source: https://leetcode.com/problems/maximum-profit-in-job-scheduling/   |   Difficulty: Hard
//
// Problem Description:
// We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].
//
// You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.
//
// If you choose a job that ends at time X you will be able to start another job that starts at time X.
//
// Example:
// Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
// Output: 120
// Explanation: The subset chosen is the first and fourth job. 
// Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
//
// Constraints:
// 1 <= startTime.length == endTime.length == profit.length <= 5 * 104
// 	1 <= startTime[i] < endTime[i] <= 109
// 	1 <= profit[i] <= 104
//

class Solution {
    public int jobScheduling(int[] startTime, int[] endTime, int[] profit) {
        int n = startTime.length;
        int[][] jobs = new int[n][3];
        for (int i = 0; i < n; i++) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        Arrays.sort(jobs, (a, b) -> Integer.compare(a[1], b[1]));

        // dp[i] - max profit by scheduling jobs[0..i]
        int[] dp = new int[n];
        dp[0] = jobs[0][2];

        for (int i = 1; i < n; i++) {
            int includeProfit = jobs[i][2];
            int l = binarySearch(jobs, i);
            if (l != -1) {
                includeProfit += dp[l];
            }
            dp[i] = Math.max(includeProfit, dp[i - 1]);
        }
        return dp[n - 1];                   
    }
}
