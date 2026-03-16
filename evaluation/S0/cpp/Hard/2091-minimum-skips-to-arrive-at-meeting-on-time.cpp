// Source: https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer hoursBefore, the number of hours you have to travel to your meeting. To arrive at your meeting, you have to travel through n roads. The road lengths are given as an integer array dist of length n, where dist[i] describes the length of the ith road in kilometers. In addition, you are given an integer speed, which is the speed (in km/h) you will travel at.
//
// After you travel road i, you must rest and wait for the next integer hour before you can begin traveling on the next road. Note that you do not have to rest after traveling the last road because you are already at the meeting.
//
//
// 	For example, if traveling a road takes 1.4 hours, you must wait until the 2 hour mark before traveling the next road. If traveling a road takes exactly 2 hours, you do not need to wait.
//
//
// However, you are allowed to skip some rests to be able to arrive on time, meaning you do not need to wait for the next integer hour. Note that this means you may finish traveling future roads at different hour marks.
//
//
// 	For example, suppose traveling the first road takes 1.4 hours and traveling the second road takes 0.6 hours. Skipping the rest after the first road will mean you finish traveling the second road right at the 2 hour mark, letting you start traveling the third road immediately.
//
//
// Return the minimum number of skips required to arrive at the meeting on time, or -1 if it is impossible.
//
// Example:
// Input: dist = [1,3,2], speed = 4, hoursBefore = 2
// Output: 1
// Explanation:
// Without skipping any rests, you will arrive in (1/4 + 3/4) + (3/4 + 1/4) + (2/4) = 2.5 hours.
// You can skip the first rest to arrive in ((1/4 + 0) + (3/4 + 0)) + (2/4) = 1.5 hours.
// Note that the second rest is shortened because you finish traveling the second road at an integer hour due to skipping the first rest.
//
// Constraints:
// n == dist.length
// 	1 <= n <= 1000
// 	1 <= dist[i] <= 105
// 	1 <= speed <= 106
// 	1 <= hoursBefore <= 107
//

class Solution {
public:
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        int n = dist.size();
        const long long INF = 1e15;
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, INF));
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; i++) {
            long long d = dist[i - 1];
            for (int j = 0; j <= i; j++) {
                // Not skip
                if (dp[i - 1][j] != INF) {
                    long long time = dp[i - 1][j] + d;
                    dp[i][j] = min(dp[i][j], (time + speed - 1) / speed * speed);
                }
                
                // Skip
                if (j > 0 && dp[i - 1][j - 1] != INF) {
                    long long time = dp[i - 1][j - 1] + d;
                    dp[i][j] = min(dp[i][j], time);
                }
            }
        }
        
        for (int j = 0; j <= n; j++) {
            if (dp[n][j] <= (long long)hoursBefore * speed) {
                return j;
            }
        }
        
        return -1;          
    }
};
