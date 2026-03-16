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

int minimumFinishTime(int** tires, int tiresSize, int* tiresColSize, int changeTime, int numLaps) {
    int maxLaps = 20; /* beyond which it's always better to change tire */
    int *minTimePerLaps = (int*)malloc((maxLaps + 1) * sizeof(int));
    for (int i = 1; i <= maxLaps; i++) minTimePerLaps[i] = 1000000000;
    for (int i = 0; i < tiresSize; i++) {
        int f = tires[i][0];
        int r = tires[i][1];
        int time = 0;
        for (int lap = 1; lap <= maxLaps; lap++) {
            time += f;
            if (time > minTimePerLaps[lap]) break;
            if (time < minTimePerLaps[lap]) minTimePerLaps[lap] = time;
            f *= r;
        }
    }
    int *dp = (int*)malloc((numLaps + 1) * sizeof(int));
    dp[0] = 0;
    for (int lap = 1; lap <= numLaps; lap++) {
        dp[lap] = 1000000000;
        for (int k = 1; k <= maxLaps && k <= lap; k++) {
            int candidate = dp[lap - k] + minTimePerLaps[k];
            if (lap > k) candidate += changeTime;
            if (candidate < dp[lap]) dp[lap] = candidate;
        }
    }
    int result = dp[numLaps];
    free(minTimePerLaps);
    free(dp);
    return result;      
}
