// Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer eventTime denoting the duration of an event, where the event occurs from time t = 0 to time t = eventTime.
//
// You are also given two integer arrays startTime and endTime, each of length n. These represent the start and end time of n non-overlapping meetings, where the ith meeting occurs during the time [startTime[i], endTime[i]].
//
// You can reschedule at most k meetings by moving their start time while maintaining the same duration, to maximize the longest continuous period of free time during the event.
//
// The relative order of all the meetings should stay the same and they should remain non-overlapping.
//
// Return the maximum amount of free time possible after rearranging the meetings.
//
// Note that the meetings can not be rescheduled to a time outside the event.
//
// Example:
// Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
//
// Output: 2
//
// Explanation:
//
//
//
// Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the time [0, 2].
//
// Constraints:
// 1 <= eventTime <= 109
// 	n == startTime.length == endTime.length
// 	2 <= n <= 105
// 	1 <= k <= n
// 	0 <= startTime[i] < endTime[i] <= eventTime
// 	endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
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
    public int maxFreeTime(int eventTime, int k, int[] startTime, int[] endTime) {
        int n = startTime.length;
        int[] dp = new int[n];
        dp[0] = endTime[0] - startTime[0];

        for (int i = 1; i < n; i++) {
            dp[i] = dp[i - 1] + endTime[i] - startTime[i];
        }

        int maxFreeTime = Math.max(startTime[0], eventTime - endTime[n - 1]);

        for (int i = 0; i < n; i++) {
            int freeTimeBefore = (i > 0) ? startTime[i] - endTime[i - 1] : startTime[0];
            int freeTimeAfter = (i < n - 1) ? startTime[i + 1] - endTime[i] : eventTime - endTime[n - 1];
            maxFreeTime = Math.max(maxFreeTime, freeTimeBefore + freeTimeAfter);
        }

        return maxFreeTime;         
    }
}
