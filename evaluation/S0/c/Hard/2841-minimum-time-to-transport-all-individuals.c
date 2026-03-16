// Source: https://leetcode.com/problems/minimum-time-to-transport-all-individuals/   |   Difficulty: Hard
//
// Problem Description:
// You are given n individuals at a base camp who need to cross a river to reach a destination using a single boat. The boat can carry at most k people at a time. The trip is affected by environmental conditions that vary cyclically over m stages.
//
// Each stage j has a speed multiplier mul[j]:
//
//
// 	If mul[j] > 1, the trip slows down.
// 	If mul[j] < 1, the trip speeds up.
//
//
// Each individual i has a rowing strength represented by time[i], the time (in minutes) it takes them to cross alone in neutral conditions.
//
// Rules:
//
//
// 	A group g departing at stage j takes time equal to the maximum time[i] among its members, multiplied by mul[j] minutes to reach the destination.
// 	After the group crosses the river in time d, the stage advances by floor(d) % m steps.
// 	If individuals are left behind, one person must return with the boat. Let r be the index of the returning person, the return takes time[r] × mul[current_stage], defined as return_time, and the stage advances by floor(return_time) % m.
//
//
// Return the minimum total time required to transport all individuals. If it is not possible to transport all individuals to the destination, return -1.
//
// Example:
// Input: n = 1, k = 1, m = 2, time = [5], mul = [1.0,1.3]
//
// Output: 5.00000
//
// Explanation:
//
//
// 	Individual 0 departs from stage 0, so crossing time = 5 × 1.00 = 5.00 minutes.
// 	All team members are now at the destination. Thus, the total time taken is 5.00 minutes.
//
// Constraints:
// 1 <= n == time.length <= 12
// 	1 <= k <= 5
// 	1 <= m <= 5
// 	1 <= time[i] <= 100
// 	m == mul.length
// 	0.5 <= mul[i] <= 2.0
//

double minTime(int n, int k, int m, int* time, int timeSize, double* mul, int mulSize) {
    int totalStates = 1 << n;
    double dp[totalStates][m];
    for (int i = 0; i < totalStates; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = 1e9;
        }
    }
    dp[0][0] = 0.0;

    for (int state = 0; state < totalStates; ++state) {
        for (int stage = 0; stage < m; ++stage) {
            if (dp[state][stage] >= 1e9) continue;

            // Generate all groups of size up to k from remaining individuals
            for (int group = 1; group < totalStates; ++group) {
                if ((group & state) != 0) continue; // already transported
                if (__builtin_popcount(group) > k) continue; // exceed boat capacity

                // Calculate crossing time
                int maxTime = 0;
                for (int i = 0; i < n; ++i) {
                    if (group & (1 << i)) {
                        if (time[i] > maxTime) maxTime = time[i];
                    }
                }
                double crossTime = maxTime * mul[stage];
                int nextStage = (stage + (int)crossTime) % m;
                double newTime = dp[state][stage] + crossTime;

                int newState = state | group;

                // If all individuals are transported, update dp without return trip
                if (newState == totalStates - 1) {
                    if (newTime < dp[newState][nextStage]) {
                        dp[newState][nextStage] = newTime;
                    }
                    continue;
                }

                // Consider return trips
                for (int ret = 0; ret < n; ++ret) {
                    if ((newState & (1 << ret)) == 0) continue; // must be in the group

                    double returnTime = time[ret] * mul[nextStage];
                    int finalStage = (nextStage + (int)returnTime) % m;
                    double totalNewTime = newTime + returnTime;

                    if (totalNewTime < dp[newState][finalStage]) {
                        dp[newState][finalStage] = totalNewTime;
                    }
                }
            }    
        }
    }
    double result = 1e9;
    for (int stage = 0; stage < m; ++stage) {
        if (dp[totalStates - 1][stage] < result) {
            result = dp[totalStates - 1][stage];
        }
    }
    return result < 1e9 ? result : -1.0;   
}
