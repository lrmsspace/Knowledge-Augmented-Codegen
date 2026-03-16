// Source: https://leetcode.com/problems/interval-list-intersections/   |   Difficulty: Medium
//
// Problem Description:
// You are given two lists of closed intervals, firstList and secondList, where firstList[i] = [starti, endi] and secondList[j] = [startj, endj]. Each list of intervals is pairwise disjoint and in sorted order.
//
// Return the intersection of these two interval lists.
//
// A closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.
//
// The intersection of two closed intervals is a set of real numbers that are either empty or represented as a closed interval. For example, the intersection of [1, 3] and [2, 4] is [2, 3].
//
// Example:
// Input: firstList = [[0,2],[5,10],[13,23],[24,25]], secondList = [[1,5],[8,12],[15,24],[25,26]]
// Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
//
// Constraints:
// 0 <= firstList.length, secondList.length <= 1000
// 	firstList.length + secondList.length >= 1
// 	0 <= starti < endi <= 109
// 	endi < starti+1
// 	0 <= startj < endj <= 109 
// 	endj < startj+1
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** intervalIntersection(int** firstList, int firstListSize, int* firstListColSize, int** secondList, int secondListSize, int* secondListColSize, int* returnSize, int** returnColumnSizes) {
    int maxSize = firstListSize + secondListSize;
    int** result = (int**)malloc(sizeof(int*) * maxSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * maxSize);
    *returnSize = 0;

    int i = 0, j = 0;
    while (i < firstListSize && j < secondListSize) {
        int start1 = firstList[i][0], end1 = firstList[i][1];
        int start2 = secondList[j][0], end2 = secondList[j][1];

        // Check if there is an intersection
        if (end1 >= start2 && end2 >= start1) {
            int startIntersect = start1 > start2 ? start1 : start2;
            int endIntersect = end1 < end2 ? end1 : end2;

            result[*returnSize] = (int*)malloc(sizeof(int) * 2);
            result[*returnSize][0] = startIntersect;
            result[*returnSize][1] = endIntersect;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }

        // Move to the next interval in the list that ends first
        if (end1 < end2) {
            i++;
        } else {
            j++;
        }
    }

    return result;      
}
