// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei. You are also given an integer k which represents the maximum number of events you can attend.
//
// You can only attend one event at a time. If you choose to attend an event, you must attend the entire event. Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.
//
// Return the maximum sum of values that you can receive by attending events.
//
// Example:
// Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
// Output: 7
// Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
//
// Constraints:
// 1 <= k <= events.length
// 	1 <= k * events.length <= 106
// 	1 <= startDayi <= endDayi <= 109
// 	1 <= valuei <= 106
//

/**
 * @param {number[][]} events
 * @param {number} k
 * @return {number}
 */
var maxValue = function(events, k) {
    events.sort((a, b) => a[0] - b[0]);
    const n = events.length;
    const dp = new Array(n).fill(0);
    dp[0] = events[0][2];
    for (let i = 1; i < n; i++) {
        dp[i] = Math.max(dp[i - 1], events[i][2]);
        for (let j = i - 1; j >= 0; j--) {
            if (events[j][1] < events[i][0]) {
                dp[i] = Math.max(dp[i], dp[j] + events[i][2]);
                break;
            }
        }    }
    const maxValues = new Array(n).fill(0);
    maxValues[0] = dp[0];
    for (let i = 1; i < n; i++) {
        maxValues[i] = Math.max(maxValues[i - 1], dp[i]);
    }
    let result = 0;
    for (let i = 0; i < n; i++) {
        const remaining = k - 1;
        if (remaining > 0) {
            const nextIndex = binarySearch(events, events[i][1]);
            if (nextIndex < n) {
                result = Math.max(result, dp[i] + maxValues[nextIndex]);
            }
        }
        else {
            result = Math.max(result, dp[i]);
        }
    }
    return result;
        
};
