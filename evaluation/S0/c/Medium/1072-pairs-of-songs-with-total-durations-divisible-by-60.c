// Source: https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/   |   Difficulty: Medium
//
// Problem Description:
// You are given a list of songs where the ith song has a duration of time[i] seconds.
//
// Return the number of pairs of songs for which their total duration in seconds is divisible by 60. Formally, we want the number of indices i, j such that i < j with (time[i] + time[j]) % 60 == 0.
//
// Example:
// Input: time = [30,20,150,100,40]
// Output: 3
// Explanation: Three pairs have a total duration divisible by 60:
// (time[0] = 30, time[2] = 150): total duration 180
// (time[1] = 20, time[3] = 100): total duration 120
// (time[1] = 20, time[4] = 40): total duration 60
//
// Constraints:
// 1 <= time.length <= 6 * 104
// 	1 <= time[i] <= 500
//

int numPairsDivisibleBy60(int* time, int timeSize) {
    int count[60] = {0};
    int result = 0;

    for (int i = 0; i < timeSize; i++) {
        int remainder = time[i] % 60;
        int complement = (60 - remainder) % 60;
        result += count[complement];
        count[remainder]++;
    }

    return result;      
}
