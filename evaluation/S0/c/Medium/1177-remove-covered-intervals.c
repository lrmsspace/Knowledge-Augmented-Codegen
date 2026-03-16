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

int removeCoveredIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    // Sort intervals by starting point ascending, and by ending point descending
    for (int i = 0; i < intervalsSize - 1; i++) {
        for (int j = 0; j < intervalsSize - i - 1; j++) {
            if (intervals[j][0] > intervals[j + 1][0] || 
               (intervals[j][0] == intervals[j + 1][0] && intervals[j][1] < intervals[j + 1][1])) {
                int* temp = intervals[j];
                intervals[j] = intervals[j + 1];
                intervals[j + 1] = temp;
            }
        }
    }

    int count = 0;
    int maxEnd = 0;

    for (int i = 0; i < intervalsSize; i++) {
        if (intervals[i][1] > maxEnd) {
            count++;
            maxEnd = intervals[i][1];
        }
    }

    return count;       
}
