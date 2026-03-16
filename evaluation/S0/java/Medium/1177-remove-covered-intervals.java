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

class Solution {
    public int removeCoveredIntervals(int[][] intervals) {
        // Sort intervals by starting point; if starting points are the same, sort by ending point in descending order
        Arrays.sort(intervals, (a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(a[0], b[0]);
            } else {
                return Integer.compare(b[1], a[1]);
            }
        });

        int count = 0;
        int end = 0;

        for (int[] interval : intervals) {
            // If the end of the current interval is greater than the end of the last added interval,
            // it means this interval is not covered
            if (interval[1] > end) {
                count++;
                end = interval[1];
            }
        }

        return count;           
    }
}
