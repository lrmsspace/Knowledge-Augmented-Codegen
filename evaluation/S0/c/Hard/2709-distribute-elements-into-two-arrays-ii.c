// Source: https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 1-indexed array of integers nums of length n.
//
// We define a function greaterCount such that greaterCount(arr, val) returns the number of elements in arr that are strictly greater than val.
//
// You need to distribute all the elements of nums between two arrays arr1 and arr2 using n operations. In the first operation, append nums[1] to arr1. In the second operation, append nums[2] to arr2. Afterwards, in the ith operation:
//
//
// 	If greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]), append nums[i] to arr1.
// 	If greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]), append nums[i] to arr2.
// 	If greaterCount(arr1, nums[i]) == greaterCount(arr2, nums[i]), append nums[i] to the array with a lesser number of elements.
// 	If there is still a tie, append nums[i] to arr1.
//
//
// The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 == [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].
//
// Return the integer array result.
//
// Example:
// Input: nums = [2,1,3,3]
// Output: [2,3,1,3]
// Explanation: After the first 2 operations, arr1 = [2] and arr2 = [1].
// In the 3rd operation, the number of elements greater than 3 is zero in both arrays. Also, the lengths are equal, hence, append nums[3] to arr1.
// In the 4th operation, the number of elements greater than 3 is zero in both arrays. As the length of arr2 is lesser, hence, append nums[4] to arr2.
// After 4 operations, arr1 = [2,3] and arr2 = [1,3].
// Hence, the array result formed by concatenation is [2,3,1,3].
//
// Constraints:
// 3 <= n <= 105
// 	1 <= nums[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultArray(int* nums, int numsSize, int* returnSize) {
    if (!returnSize || numsSize < 3) return NULL;

    int *res = (int*)malloc(numsSize * sizeof(int));
    if (!res) return NULL;

    int *arr1 = (int*)malloc(numsSize * sizeof(int));
    int *arr2 = (int*)malloc(numsSize * sizeof(int));
    if (!arr1 || !arr2) {
        free(res); free(arr1); free(arr2);
        return NULL;
    }

    int size1 = 0, size2 = 0;
    int count1 = 0, count2 = 0;

    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        if (i == 0) {
            arr1[size1++] = val;
        } else if (i == 1) {
            arr2[size2++] = val;
        } else {
            // Count elements greater than val in arr1
            count1 = 0;
            for (int j = 0; j < size1; ++j) {
                if (arr1[j] > val) count1++;
            }
            // Count elements greater than val in arr2
            count2 = 0;
            for (int j = 0; j < size2; ++j) {
                if (arr2[j] > val) count2++;
            }

            if (count1 > count2) {
                arr1[size1++] = val;
            } else if (count1 < count2) {
                arr2[size2++] = val;
            } else {
                if (size1 <= size2) {
                    arr1[size1++] = val;
                } else {
                    arr2[size2++] = val;
                }
            }
        }
    }

    // Concatenate arr1 and arr2 into res
    for (int i = 0; i < size1; ++i) {
        res[i] = arr1[i];
    }
    for (int i = 0; i < size2; ++i) {
        res[size1 + i] = arr2[i];
    }

    *returnSize = numsSize;

    free(arr1);
    free(arr2);

    return res;     
}
