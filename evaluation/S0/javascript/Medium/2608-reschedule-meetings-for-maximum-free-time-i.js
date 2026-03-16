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

/**
 * @param {number} eventTime
 * @param {number} k
 * @param {number[]} startTime
 * @param {number[]} endTime
 * @return {number}
 */
var maxFreeTime = function(eventTime, k, startTime, endTime) {
    const n = startTime.length;
    const meetings = [];
    for (let i = 0; i < n; i++) {
        meetings.push([startTime[i], endTime[i]]);
    }
    meetings.sort((a, b) => a[0] - b[0]);
    const gaps = [];
    for (let i = 1; i < n; i++) {
        const gap = meetings[i][0] - meetings[i - 1][1];
        if (gap > 0) {
            gaps.push(gap);
        }
    }
    gaps.sort((a, b) => b - a);
    let maxFreeTime = 0;
    for (let i = 0; i < k && i < gaps.length; i++) {
        maxFreeTime += gaps[i];
    }
    return Math.min(maxFreeTime, eventTime - (meetings[n - 1][1] - meetings[0][0]));    
};
