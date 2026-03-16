// Source: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr.
//
// We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.
//
// Return the largest number of chunks we can make to sort the array.
//
// Example:
// Input: arr = [5,4,3,2,1]
// Output: 1
// Explanation:
// Splitting into two or more chunks will not return the required result.
// For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
//
// Constraints:
// 1 <= arr.length <= 2000
// 	0 <= arr[i] <= 108
//

int maxChunksToSorted(int* arr, int arrSize) {
    if (arrSize <= 1) return arrSize;

    int *leftMax = (int*)malloc(arrSize * sizeof(int));
    if (!leftMax) return 0; /* allocation failure */

    leftMax[0] = arr[0];
    for (int i = 1; i < arrSize; ++i) {
        leftMax[i] = (arr[i] > leftMax[i - 1]) ? arr[i] : leftMax[i - 1];
    }

    int rightMin = arr[arrSize - 1];
    int chunks = 0;
    for (int i = arrSize - 1; i >= 0; --i) {
        if (leftMax[i] <= rightMin) {
            ++chunks;
        }
        if (arr[i] < rightMin) {
            rightMin = arr[i];
        }
    }

    free(leftMax);
    return chunks;      
}
