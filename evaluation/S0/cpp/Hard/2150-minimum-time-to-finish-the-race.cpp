// Source: https://leetcode.com/problems/minimum-time-to-finish-the-race/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array tires where tires[i] = [fi, ri] indicates that the ith tire can finish its xth successive lap in fi * ri(x-1) seconds.
//
//
// 	For example, if fi = 3 and ri = 2, then the tire would finish its 1st lap in 3 seconds, its 2nd lap in 3 * 2 = 6 seconds, its 3rd lap in 3 * 22 = 12 seconds, etc.
//
//
// You are also given an integer changeTime and an integer numLaps.
//
// The race consists of numLaps laps and you may start the race with any tire. You have an unlimited supply of each tire and after every lap, you may change to any given tire (including the current tire type) if you wait changeTime seconds.
//
// Return the minimum time to finish the race.
//
// Example:
// Input: tires = [[2,3],[3,4]], changeTime = 5, numLaps = 4
// Output: 21
// Explanation: 
// Lap 1: Start with tire 0 and finish the lap in 2 seconds.
// Lap 2: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Lap 3: Change tires to a new tire 0 for 5 seconds and then finish the lap in another 2 seconds.
// Lap 4: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Total time = 2 + 6 + 5 + 2 + 6 = 21 seconds.
// The minimum time to complete the race is 21 seconds.
//
// Constraints:
// 1 <= tires.length <= 105
// 	tires[i].length == 2
// 	1 <= fi, changeTime <= 105
// 	2 <= ri <= 105
// 	1 <= numLaps <= 1000
//

class Solution {
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        vector<int> dp(numLaps + 1, INT_MAX);
        dp[0] = 0;
        
        // Precompute best times for consecutive laps without changing tires
        vector<int> bestLapTimes(numLaps + 1, INT_MAX);
        
        for (const auto& tire : tires) {
            int f = tire[0];
            int r = tire[1];
            long long time = 0;
            for (int laps = 1; laps <= numLaps; ++laps) {
                time += f * pow(r, laps - 1);
                if (time > 1e9) break; // Prevent overflow
                bestLapTimes[laps] = min(bestLapTimes[laps], (int)time);
            }
        }
        
        // DP to find minimum time to finish numLaps
        for (int laps = 1; laps <= numLaps; ++laps) {
            for (int k = 1; k <= laps; ++k) {
                dp[laps] = min(dp[laps], dp[laps - k] + bestLapTimes[k] + (laps - k > 0 ? changeTime : 0));
            }
        }
        
        return dp[numLaps];         
    }
};
