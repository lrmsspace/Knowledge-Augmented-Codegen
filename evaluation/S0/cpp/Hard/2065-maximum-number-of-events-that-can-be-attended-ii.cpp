// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei. You are also given an integer k which represents the maximum number of events you can attend.
//
// You can only attend one event at a time. If you choose to attend an event, you must attend the entire event. Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.
//
// Return the maximum sum of values that you can receive by attending events.
//
// Example:
// Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
// Output: 7
// Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
//
// Constraints:
// 1 <= k <= events.length
// 	1 <= k * events.length <= 106
// 	1 <= startDayi <= endDayi <= 109
// 	1 <= valuei <= 106
//

class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        sort(events.begin(), events.end());
        
        // dp[i][j]: max value by attending j events among first i events
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            int start = events[i - 1][0];
            int end = events[i - 1][1];
            int value = events[i - 1][2];
            
            // Find the last event that ends before start
            int l = 0, r = i - 1;
            int lastNonOverlap = 0;
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (events[mid][1] < start) {
                    lastNonOverlap = mid + 1;
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            
            for (int j = 1; j <= k; j++) {
                // Not attend this event
                dp[i][j] = dp[i - 1][j];
                
                // Attend this event
                dp[i][j] = max(dp[i][j], dp[lastNonOverlap][j - 1] + value);
            }
        }
        
        return dp[n][k];            
    }
};
