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

int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int* profit, int profitSize) {
    typedef struct {
        int start;
        int end;
        int profit;
    } Job;

    int n = startTimeSize;
    Job* jobs = (Job*)malloc(n * sizeof(Job));
    for (int i = 0; i < n; ++i) {
        jobs[i].start = startTime[i];
        jobs[i].end = endTime[i];
        jobs[i].profit = profit[i];
    }

    // Sort jobs by end time
    qsort(jobs, n, sizeof(Job), [](const void* a, const void* b) {
        return ((Job*)a)->end - ((Job*)b)->end;
    });

    // DP array to store maximum profit until each job
    int* dp = (int*)malloc((n + 1) * sizeof(int));
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        // Profit including the current job
        int includeProfit = jobs[i - 1].profit;

        // Find the last non-conflicting job using binary search
        int left = 0, right = i - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (jobs[mid].end <= jobs[i - 1].start) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        includeProfit += dp[left];

        // Maximum profit at this point
        dp[i] = (includeProfit > dp[i - 1]) ? includeProfit : dp[i - 1];
    }

    int result = dp[n];
    free(jobs);
    free(dp);
    return result;      
}
