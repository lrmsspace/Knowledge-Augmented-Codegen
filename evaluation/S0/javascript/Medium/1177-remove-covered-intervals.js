// Source: https://leetcode.com/problems/remove-covered-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), remove all intervals that are covered by another interval in the list.
//
// The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
//
// Return the number of remaining intervals.
//
// Example:
// Input: intervals = [[1,4],[3,6],[2,8]]
// Output: 2
// Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
//
// Constraints:
// 1 <= intervals.length <= 1000
// 	intervals[i].length == 2
// 	0 <= li < ri <= 105
// 	All the given intervals are unique.
//

/**
 * @param {number[][]} intervals
 * @return {number}
 */
var removeCoveredIntervals = function(intervals) {
    // Sort intervals by starting point ascending, and by ending point descending
    intervals.sort((a, b) => a[0] - b[0] || b[1] - a[1]);
    let count = 0;
    let end = 0;
    for (const interval of intervals) {
        if (interval[1] > end) {
            count++;
            end = interval[1];
        }
    }
    return count;
        
};
