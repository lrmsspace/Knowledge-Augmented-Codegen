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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numPairsDivisibleBy60(int[] time) {
        int[] count = new int[60];
        int pairs = 0;

        for (int t : time) {
            int remainder = t % 60;
            int complement = (60 - remainder) % 60; // Handle the case when remainder is 0
            pairs += count[complement];
            count[remainder]++;
        }

        return pairs;           
    }
}
