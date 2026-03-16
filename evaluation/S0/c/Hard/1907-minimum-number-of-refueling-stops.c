// Source: https://leetcode.com/problems/minimum-number-of-refueling-stops/   |   Difficulty: Hard
//
// Problem Description:
// A car travels from a starting position to a destination which is target miles east of the starting position.
//
// There are gas stations along the way. The gas stations are represented as an array stations where stations[i] = [positioni, fueli] indicates that the ith gas station is positioni miles east of the starting position and has fueli liters of gas.
//
// The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it. It uses one liter of gas per one mile that it drives. When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.
//
// Return the minimum number of refueling stops the car must make in order to reach its destination. If it cannot reach the destination, return -1.
//
// Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there. If the car reaches the destination with 0 fuel left, it is still considered to have arrived.
//
// Example:
// Input: target = 1, startFuel = 1, stations = []
// Output: 0
// Explanation: We can reach the target without refueling.
//
// Constraints:
// 1 <= target, startFuel <= 109
// 	0 <= stations.length <= 500
// 	1 <= positioni < positioni+1 < target
// 	1 <= fueli < 109
//

int minRefuelStops(int target, int startFuel, int** stations, int stationsSize, int* stationsColSize) {
    /* dp[i] = farthest distance can reach with i refuels */
    long *dp = (long*)calloc(stationsSize + 1, sizeof(long));
    if (!dp) return -1;
    dp[0] = startFuel;

    for (int i = 0; i < stationsSize; ++i) {
        int pos = stations[i][0];
        int fuel = stations[i][1];
        for (int j = i; j >= 0; --j) {
            if (dp[j] >= pos) {
                long cand = dp[j] + fuel;
                if (cand > dp[j + 1]) dp[j + 1] = cand;
            }
        }
    }

    int res = -1;
    for (int i = 0; i <= stationsSize; ++i) {
        if (dp[i] >= target) {
            res = i;
            break;
        }
    }
    free(dp);
    return res;     
}
