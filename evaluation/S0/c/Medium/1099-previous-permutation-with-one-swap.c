// Source: https://leetcode.com/problems/previous-permutation-with-one-swap/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers arr (not necessarily distinct), return the lexicographically largest permutation that is smaller than arr, that can be made with exactly one swap. If it cannot be done, then return the same array.
//
// Note that a swap exchanges the positions of two numbers arr[i] and arr[j]
//
// Example:
// Input: arr = [3,2,1]
// Output: [3,1,2]
// Explanation: Swapping 2 and 1.
//
// Constraints:
// 1 <= arr.length <= 104
// 	1 <= arr[i] <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* prevPermOpt1(int* arr, int arrSize, int* returnSize) {
    int i, j, maxIdx;
    *returnSize = arrSize;

    // Find the first decreasing element from the right
    for (i = arrSize - 2; i >= 0; i--) {
        if (arr[i] > arr[i + 1]) {
            break;
        }
    }

    // If no such element is found, return the original array
    if (i < 0) {
        return arr;
    }

    // Find the largest element to the right of arr[i] that is smaller than arr[i]
    maxIdx = -1;
    for (j = arrSize - 1; j > i; j--) {
        if (arr[j] < arr[i]) {
            if (maxIdx == -1 || arr[j] >= arr[maxIdx]) {
                maxIdx = j;
            }
        }
    }

    // Swap the found elements
    if (maxIdx != -1) {
        int temp = arr[i];
        arr[i] = arr[maxIdx];
        arr[maxIdx] = temp;
    }

    return arr;     
}
