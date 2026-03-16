// Source: https://leetcode.com/problems/set-intersection-size-at-least-two/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals where intervals[i] = [starti, endi] represents all the integers from starti to endi inclusively.
//
// A containing set is an array nums where each interval from intervals has at least two integers in nums.
//
//
// 	For example, if intervals = [[1,3], [3,7], [8,9]], then [1,2,4,7,8,9] and [2,3,4,8,9] are containing sets.
//
//
// Return the minimum possible size of a containing set.
//
// Example:
// Input: intervals = [[1,3],[3,7],[8,9]]
// Output: 5
// Explanation: let nums = [2, 3, 4, 8, 9].
// It can be shown that there cannot be any containing array of size 4.
//
// Constraints:
// 1 <= intervals.length <= 3000
// 	intervals[i].length == 2
// 	0 <= starti < endi <= 108
//

int intersectionSizeTwo(int** intervals, int intervalsSize, int* intervalsColSize) {
    if (intervalsSize <= 0 || !intervalsColSize) return 0;

    /* sort intervals by end ascending, start descending */
    int cmp(const void *a, const void *b) {
        const int *ia = *(const int**)a;
        const int *ib = *(const int**)b;
        if (ia[1] != ib[1]) return ia[1] - ib[1];
        return ib[0] - ia[0];
    }
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    int res = 0;
    int first = -1, second = -1; /* two largest numbers in the current set */

    for (int i = 0; i < intervalsSize; ++i) {
        int start = intervals[i][0];
        int end = intervals[i][1];

        if (second < start) {
            /* no overlap, need to add two new numbers */
            res += 2;
            first = end - 1;
            second = end;
        } else if (first < start) {
            /* partial overlap, need to add one new number */
            res += 1;
            first = second;
            second = end;
        }
        /* else: full overlap, do nothing */
    }

    return res;     
}
