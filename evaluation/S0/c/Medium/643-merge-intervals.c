// Source: https://leetcode.com/problems/merge-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
//
// Example:
// Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
//
// Constraints:
// 1 <= intervals.length <= 104
// 	intervals[i].length == 2
// 	0 <= starti <= endi <= 104
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    // Sort intervals based on the start time
    int cmp(const void* a, const void* b) {
        return (*(int**)a)[0] - (*(int**)b)[0];
    }
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    // Allocate memory for the result
    int** merged = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));
    int mergedSize = 0;

    for (int i = 0; i < intervalsSize; i++) {
        // If merged is empty or there is no overlap, add the interval
        if (mergedSize == 0 || merged[mergedSize - 1][1] < intervals[i][0]) {
            merged[mergedSize] = (int*)malloc(2 * sizeof(int));
            merged[mergedSize][0] = intervals[i][0];
            merged[mergedSize][1] = intervals[i][1];
            (*returnColumnSizes)[mergedSize] = 2;
            mergedSize++;
        } else {
            // There is an overlap, merge the intervals
            if (merged[mergedSize - 1][1] < intervals[i][1]) {
                merged[mergedSize - 1][1] = intervals[i][1];
            }
        }
    }

    *returnSize = mergedSize;
    return merged;      
}
