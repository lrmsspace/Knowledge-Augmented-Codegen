// Source: https://leetcode.com/problems/sort-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums, sort the array in ascending order and return it.
//
// You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.
//
// Example:
// Input: nums = [5,2,3,1]
// Output: [1,2,3,5]
// Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-5 * 104 <= nums[i] <= 5 * 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
    // Implementing Merge Sort
    void merge(int* arr, int left, int mid, int right, int* temp) {
        int i = left;    // Starting index for left subarray
        int j = mid + 1; // Starting index for right subarray
        int k = left;    // Starting index to be sorted

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        for (i = left; i <= right; i++) {
            arr[i] = temp[i];
        }
    }

    void mergeSort(int* arr, int left, int right, int* temp) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, temp);
            mergeSort(arr, mid + 1, right, temp);
            merge(arr, left, mid, right, temp);
        }
    }

    int* temp = (int*)malloc(numsSize * sizeof(int));
    mergeSort(nums, 0, numsSize - 1, temp);
    free(temp);

    *returnSize = numsSize;
    return nums;        
}
