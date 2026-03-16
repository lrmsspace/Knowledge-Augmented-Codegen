// Source: https://leetcode.com/problems/insert-interval/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
//
// Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
//
// Return intervals after the insertion.
//
// Note that you don't need to modify intervals in-place. You can make a new array and return it.
//
// Example:
// Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Output: [[1,5],[6,9]]
//
// Constraints:
// 0 <= intervals.length <= 104
// 	intervals[i].length == 2
// 	0 <= starti <= endi <= 105
// 	intervals is sorted by starti in ascending order.
// 	newInterval.length == 2
// 	0 <= start <= end <= 105
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc((intervalsSize + 1) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((intervalsSize + 1) * sizeof(int));
    int idx = 0, resIdx = 0;

    // Add all intervals ending before newInterval starts
    while (idx < intervalsSize && intervals[idx][1] < newInterval[0]) {
        result[resIdx] = (int*)malloc(2 * sizeof(int));
        result[resIdx][0] = intervals[idx][0];
        result[resIdx][1] = intervals[idx][1];
        (*returnColumnSizes)[resIdx] = 2;
        resIdx++;
        idx++;
    }

    // Merge overlapping intervals with newInterval
    while (idx < intervalsSize && intervals[idx][0] <= newInterval[1]) {
        newInterval[0] = fmin(newInterval[0], intervals[idx][0]);
        newInterval[1] = fmax(newInterval[1], intervals[idx][1]);
        idx++;
    }
    result[resIdx] = (int*)malloc(2 * sizeof(int));
    result[resIdx][0] = newInterval[0];
    result[resIdx][1] = newInterval[1];
    (*returnColumnSizes)[resIdx] = 2;
    resIdx++;

    // Add remaining intervals
    while (idx < intervalsSize) {
        result[resIdx] = (int*)malloc(2 * sizeof(int));
        result[resIdx][0] = intervals[idx][0];
        result[resIdx][1] = intervals[idx][1];
        (*returnColumnSizes)[resIdx] = 2;
        resIdx++;
        idx++;
    }

    *returnSize = resIdx;
    return result;      
}
