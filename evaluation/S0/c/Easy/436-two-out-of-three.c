// Source: https://leetcode.com/problems/two-out-of-three/   |   Difficulty: Easy
//
// Problem Description:
// Given three integer arrays nums1, nums2, and nums3, return a distinct array containing all the values that are present in at least two out of the three arrays. You may return the values in any order.
//
// Example:
// Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
// Output: [3,2]
// Explanation: The values that are present in at least two arrays are:
// - 3, in all three arrays.
// - 2, in nums1 and nums2.
//
// Constraints:
// 1 <= nums1.length, nums2.length, nums3.length <= 100
// 	1 <= nums1[i], nums2[j], nums3[k] <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoOutOfThree(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* returnSize) {
    int count[101] = {0};
    int *result = (int *)malloc(101 * sizeof(int));
    *returnSize = 0;

    // Mark presence in nums1
    for (int i = 0; i < nums1Size; i++) {
        count[nums1[i]] |= 1;
    }

    // Mark presence in nums2
    for (int i = 0; i < nums2Size; i++) {
        count[nums2[i]] |= 2;
    }

    // Mark presence in nums3
    for (int i = 0; i < nums3Size; i++) {
        count[nums3[i]] |= 4;
    }

    // Collect numbers present in at least two arrays
    for (int i = 1; i <= 100; i++) {
        if (__builtin_popcount(count[i]) >= 2) {
            result[(*returnSize)++] = i;
        }
    }

    return result;      
}
