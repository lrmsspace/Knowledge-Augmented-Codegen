// Source: https://leetcode.com/problems/find-right-interval/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.
//
// The right interval for an interval i is an interval j such that startj >= endi and startj is minimized. Note that i may equal j.
//
// Return an array of right interval indices for each interval i. If no right interval exists for interval i, then put -1 at index i.
//
// Example:
// Input: intervals = [[1,2]]
// Output: [-1]
// Explanation: There is only one interval in the collection, so it outputs -1.
//
// Constraints:
// 1 <= intervals.length <= 2 * 104
// 	intervals[i].length == 2
// 	-106 <= starti <= endi <= 106
// 	The start point of each interval is unique.
//

/**
 * @param {number[][]} intervals
 * @return {number[]}
 */
var findRightInterval = function(intervals) {
    const n = intervals.length;
    const result = new Array(n).fill(-1);
    const starts = intervals.map((interval, index) => [interval[0], index]);
    starts.sort((a, b) => a[0] - b[0]);
    const binarySearch = (target) => {
        let left = 0;
        let right = n - 1;
        let ans = -1;
        while (left <= right) {
            const mid = Math.floor((left + right) / 2);
            if (starts[mid][0] >= target) {
                ans = starts[mid][1];
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return ans;
    }
};
