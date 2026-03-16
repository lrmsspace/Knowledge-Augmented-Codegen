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

int eraseOverlapIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    // Sort intervals based on their end times
    qsort(intervals, intervalsSize, sizeof(int*), [](const void* a, const void* b) {
        return (*(int**)a)[1] - (*(int**)b)[1];
    });

    int count = 0; // Count of non-overlapping intervals
    int end = INT_MIN; // End time of the last added interval

    for (int i = 0; i < intervalsSize; i++) {
        if (intervals[i][0] >= end) {
            // If the current interval does not overlap, include it
            end = intervals[i][1];
            count++;
        }
    }

    // The minimum number of intervals to remove is total intervals minus non-overlapping count
    return intervalsSize - count;       
}
