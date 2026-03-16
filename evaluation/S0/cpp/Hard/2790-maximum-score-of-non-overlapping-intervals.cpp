// Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.
//
// Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.
//
// Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
//
// Example:
// Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
//
// Output: [2,3]
//
// Explanation:
//
// You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
//
// Constraints:
// 1 <= intevals.length <= 5 * 104
// 	intervals[i].length == 3
// 	intervals[i] = [li, ri, weighti]
// 	1 <= li <= ri <= 109
// 	1 <= weighti <= 109
//

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<vector<pair<long long, vector<int>>>> dp(n + 1, vector<pair<long long, vector<int>>>(5, {0, {}}));
        
        // Sort intervals by end time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        for (int i = 1; i <= n; i++) {
            int l = intervals[i - 1][0], r = intervals[i - 1][1], w = intervals[i - 1][2];
            
            // Find the last non-overlapping interval
            int j = i - 1;
            while (j > 0 && intervals[j - 1][1] >= l) {
                j--;
            }
            
            for (int k = 1; k <= 4; k++) {
                // Not take current interval
                dp[i][k] = dp[i - 1][k];
                
                // Take current interval
                long long newWeight = dp[j][k - 1].first + w;
                if (newWeight > dp[i][k].first || 
                    (newWeight == dp[i][k].first && lexicographicallySmaller(dp[j][k - 1].second, i - 1, dp[i][k].second))) {
                    dp[i][k].first = newWeight;
                    dp[i][k].second = dp[j][k - 1].second;
                    dp[i][k].second.push_back(i - 1);
                }
            }
        }
        
        // Find the best among dp[n][1] to dp[n][4]
        pair<long long, vector<int>> best = {0, {}};
        for (int k = 1; k <= 4; k++) {
            if (dp[n][k].first > best.first || 
                (dp[n][k].first == best.first && lexicographicallySmaller(dp[n][k].second, -1, best.second))) {
                best = dp[n][k];
            }
        }
        
        return best.second;         
    }
};
