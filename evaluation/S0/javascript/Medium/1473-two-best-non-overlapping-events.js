// Source: https://leetcode.com/problems/two-best-non-overlapping-events/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.
//
// Return this maximum sum.
//
// Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at or after t + 1.
//
// Example:
// Input: events = [[1,3,2],[4,5,2],[2,4,3]]
// Output: 4
// Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
//
// Constraints:
// 2 <= events.length <= 105
// 	events[i].length == 3
// 	1 <= startTimei <= endTimei <= 109
// 	1 <= valuei <= 106
//

/**
 * @param {number[][]} events
 * @return {number}
 */
var maxTwoEvents = function(events) {
    events.sort((a, b) => a[0] - b[0]);
    const n = events.length;
    const maxValueFromEnd = new Array(n).fill(0);
    maxValueFromEnd[n - 1] = events[n - 1][2];
    for (let i = n - 2; i >= 0; i--) {
        maxValueFromEnd[i] = Math.max(maxValueFromEnd[i + 1], events[i][2]);
    }
    let maxSum = 0;
    for (let i = 0; i < n; i++) {
        const [start, end, value] = events[i];
        let left = i + 1;
        let right = n - 1;
        let nextIndex = n;
        while (left <= right) {
            const mid = Math.floor((left + right) / 2);
            if (events[mid][0] > end) {
                nextIndex = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        const totalValue = value + (nextIndex < n ? maxValueFromEnd[nextIndex] : 0);
        maxSum = Math.max(maxSum, totalValue);
    }
    return maxSum;  
};
