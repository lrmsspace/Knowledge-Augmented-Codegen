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
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<tuple<int, int, int>> jobs;
        for (int i = 0; i < n; i++) {
            jobs.emplace_back(endTime[i], startTime[i], profit[i]);
        }
        sort(jobs.begin(), jobs.end());
        
        // dp[i]: max profit by considering jobs[0..i]
        vector<long long> dp(n, 0);
        dp[0] = get<2>(jobs[0]);
        
        for (int i = 1; i < n; i++) {
            long long includeProfit = get<2>(jobs[i]);
            // Find the last non-conflicting job
            int l = 0, r = i - 1;
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (get<0>(jobs[mid]) <= get<1>(jobs[i])) {
                    includeProfit += dp[mid];
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            dp[i] = max(dp[i - 1], includeProfit);
        }
        
        return dp[n - 1];           
    }
};
