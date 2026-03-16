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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    typedef struct {
        int start;
        int index;
    } IntervalStart;

    int compare(const void* a, const void* b) {
        IntervalStart* intervalA = (IntervalStart*)a;
        IntervalStart* intervalB = (IntervalStart*)b;
        return intervalA->start - intervalB->start;
    }

    IntervalStart* starts = (IntervalStart*)malloc(intervalsSize * sizeof(IntervalStart));
    for (int i = 0; i < intervalsSize; i++) {
        starts[i].start = intervals[i][0];
        starts[i].index = i;
    }

    qsort(starts, intervalsSize, sizeof(IntervalStart), compare);

    int* result = (int*)malloc(intervalsSize * sizeof(int));
    for (int i = 0; i < intervalsSize; i++) {
        int end = intervals[i][1];
        int left = 0, right = intervalsSize - 1;
        int foundIndex = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (starts[mid].start >= end) {
                foundIndex = starts[mid].index;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        result[i] = foundIndex;
    }

    free(starts);
    *returnSize = intervalsSize;
    return result;      
}
