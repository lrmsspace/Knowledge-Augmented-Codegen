// Source: https://leetcode.com/problems/advantage-shuffle/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 both of the same length. The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].
//
// Return any permutation of nums1 that maximizes its advantage with respect to nums2.
//
// Example:
// Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
// Output: [2,11,7,15]
//
// Constraints:
// 1 <= nums1.length <= 105
// 	nums2.length == nums1.length
// 	0 <= nums1[i], nums2[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* advantageCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* sorted_nums1 = (int*)malloc(nums1Size * sizeof(int));
    int* result = (int*)malloc(nums1Size * sizeof(int));
    int* indices = (int*)malloc(nums2Size * sizeof(int));
    for (int i = 0; i < nums1Size; i++) {
        sorted_nums1[i] = nums1[i];
        indices[i] = i;
    }

    // Sort nums1
    qsort(sorted_nums1, nums1Size, sizeof(int), (int (*)(const void*, const void*))compare);

    // Sort indices of nums2 based on the values in nums2
    qsort(indices, nums2Size, sizeof(int), (int (*)(const void*, const void*))compare_indices, nums2);

    int left = 0;
    int right = nums1Size - 1;

    for (int i = 0; i < nums2Size; i++) {
        if (sorted_nums1[right] > nums2[indices[i]]) {
            result[indices[i]] = sorted_nums1[right];
            right--;
        } else {
            result[indices[i]] = sorted_nums1[left];
            left++;
        }
    }

    *returnSize = nums1Size;
    free(sorted_nums1);
    free(indices);
    return result;      
}
