// Source: https://leetcode.com/problems/non-overlapping-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
//
// Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.
//
// Example:
// Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
// Output: 1
// Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	intervals[i].length == 2
// 	-5 * 104 <= starti < endi <= 5 * 104
//

class Solution {
    public int eraseOverlapIntervals(int[][] intervals) {
        if (intervals.length == 0) {
            return 0;
        }

        // Sort intervals based on their end times
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[1], b[1]));

        int count = 0; // Count of non-overlapping intervals
        int end = intervals[0][1]; // End time of the last added interval

        for (int i = 1; i < intervals.length; i++) {
            // If the start time of the current interval is greater than or equal to
            // the end time of the last added interval, it doesn't overlap
            if (intervals[i][0] >= end) {
                count++;
                end = intervals[i][1]; // Update the end time to the current interval's end time
            }
        }

        // The minimum number of intervals to remove is total intervals minus non-overlapping count
        return intervals.length - (count + 1);          
    }
}
