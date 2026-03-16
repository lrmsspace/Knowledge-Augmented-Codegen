// Source: https://leetcode.com/problems/intersection-of-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.
//
// Example:
// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2]
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	0 <= nums1[i], nums2[i] <= 1000
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int hash[1001] = {0};
    int *result = (int *)malloc(sizeof(int) * (nums1Size < nums2Size ? nums1Size : nums2Size));
    int count = 0;

    for (int i = 0; i < nums1Size; i++) {
        hash[nums1[i]] = 1;
    }

    for (int i = 0; i < nums2Size; i++) {
        if (hash[nums2[i]] == 1) {
            result[count++] = nums2[i];
            hash[nums2[i]] = 0; // Ensure uniqueness
        }
    }

    *returnSize = count;
    return result;      
}
