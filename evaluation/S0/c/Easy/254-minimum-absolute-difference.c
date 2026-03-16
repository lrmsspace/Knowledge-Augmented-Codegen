// Source: https://leetcode.com/problems/minimum-absolute-difference/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of distinct integers arr, find all pairs of elements with the minimum absolute difference of any two elements.
//
// Return a list of pairs in ascending order(with respect to pairs), each pair [a, b] follows
//
//
// 	a, b are from arr
// 	a < b
// 	b - a equals to the minimum absolute difference of any two elements in arr
//
// Example:
// Input: arr = [4,2,1,3]
// Output: [[1,2],[2,3],[3,4]]
// Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
//
// Constraints:
// 2 <= arr.length <= 105
// 	-106 <= arr[i] <= 106
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    // Sort the array
    qsort(arr, arrSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // Find the minimum absolute difference
    int minDiff = INT_MAX;
    for (int i = 1; i < arrSize; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    // Collect pairs with the minimum absolute difference
    int** result = malloc(arrSize * sizeof(int*));
    *returnColumnSizes = malloc(arrSize * sizeof(int));
    *returnSize = 0;

    for (int i = 1; i < arrSize; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff == minDiff) {
            result[*returnSize] = malloc(2 * sizeof(int));
            result[*returnSize][0] = arr[i - 1];
            result[*returnSize][1] = arr[i];
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
    }

    return result;      
}
