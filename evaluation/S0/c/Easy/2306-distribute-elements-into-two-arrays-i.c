// Source: https://leetcode.com/problems/distribute-elements-into-two-arrays-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 1-indexed array of distinct integers nums of length n.
//
// You need to distribute all the elements of nums between two arrays arr1 and arr2 using n operations. In the first operation, append nums[1] to arr1. In the second operation, append nums[2] to arr2. Afterwards, in the ith operation:
//
//
// 	If the last element of arr1 is greater than the last element of arr2, append nums[i] to arr1. Otherwise, append nums[i] to arr2.
//
//
// The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 == [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].
//
// Return the array result.
//
// Example:
// Input: nums = [2,1,3]
// Output: [2,3,1]
// Explanation: After the first 2 operations, arr1 = [2] and arr2 = [1].
// In the 3rd operation, as the last element of arr1 is greater than the last element of arr2 (2 > 1), append nums[3] to arr1.
// After 3 operations, arr1 = [2,3] and arr2 = [1].
// Hence, the array result formed by concatenation is [2,3,1].
//
// Constraints:
// 3 <= n <= 50
// 	1 <= nums[i] <= 100
// 	All elements in nums are distinct.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultArray(int* nums, int numsSize, int* returnSize) {
    int* arr1 = (int*)malloc(numsSize * sizeof(int));
    int* arr2 = (int*)malloc(numsSize * sizeof(int));
    int size1 = 0, size2 = 0;

    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            arr1[size1++] = nums[i];
        } else {
            arr2[size2++] = nums[i];
        }
    }

    for (int i = 2; i < numsSize; i++) {
        if (arr1[size1 - 1] > arr2[size2 - 1]) {
            arr1[size1++] = nums[i];
        } else {
            arr2[size2++] = nums[i];
        }
    }

    int* result = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < size1; i++) {
        result[i] = arr1[i];
    }
    for (int i = 0; i < size2; i++) {
        result[size1 + i] = arr2[i];
    }

    *returnSize = numsSize;
    free(arr1);
    free(arr2);
    return result;      
}
