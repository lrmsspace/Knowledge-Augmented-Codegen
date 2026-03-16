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

class Solution {
    public int[] findRightInterval(int[][] intervals) {
        int n = intervals.length;
        int[][] startWithIndex = new int[n][2];
        for (int i = 0; i < n; i++) {
            startWithIndex[i][0] = intervals[i][0];
            startWithIndex[i][1] = i;
        }
        Arrays.sort(startWithIndex, (a, b) -> Integer.compare(a[0], b[0]));

        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            int end = intervals[i][1];
            int left = 0, right = n - 1;
            int idx = -1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (startWithIndex[mid][0] >= end) {
                    idx = startWithIndex[mid][1];
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            result[i] = idx;
        }
        return result;          
    }
}
