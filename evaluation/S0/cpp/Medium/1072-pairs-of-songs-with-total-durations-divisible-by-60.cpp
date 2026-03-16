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

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int> remainderCount(60, 0);
        int pairCount = 0;

        for (int t : time) {
            int remainder = t % 60;
            int complement = (60 - remainder) % 60;
            pairCount += remainderCount[complement];
            remainderCount[remainder]++;
        }

        return pairCount;           
    }
};
