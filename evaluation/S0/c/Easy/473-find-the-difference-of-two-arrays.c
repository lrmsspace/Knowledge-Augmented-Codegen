// Source: https://leetcode.com/problems/find-the-difference-of-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two 0-indexed integer arrays nums1 and nums2, return a list answer of size 2 where:
//
//
// 	answer[0] is a list of all distinct integers in nums1 which are not present in nums2.
// 	answer[1] is a list of all distinct integers in nums2 which are not present in nums1.
//
//
// Note that the integers in the lists may be returned in any order.
//
// Example:
// Input: nums1 = [1,2,3], nums2 = [2,4,6]
// Output: [[1,3],[4,6]]
// Explanation:
// For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1 and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3].
// For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and nums2[2] = 6 are not present in nums1. Therefore, answer[1] = [4,6].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	-1000 <= nums1[i], nums2[i] <= 1000
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findDifference(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize, int** returnColumnSizes) {
    int hash1[2001] = {0};
    int hash2[2001] = {0};
    for (int i = 0; i < nums1Size; i++) {
        hash1[nums1[i] + 1000] = 1;
    }
    for (int i = 0; i < nums2Size; i++) {
        hash2[nums2[i] + 1000] = 1;
    }

    int **result = (int **)malloc(2 * sizeof(int *));
    *returnColumnSizes = (int *)malloc(2 * sizeof(int));
    (*returnColumnSizes)[0] = 0;
    (*returnColumnSizes)[1] = 0;

    result[0] = (int *)malloc(nums1Size * sizeof(int));
    result[1] = (int *)malloc(nums2Size * sizeof(int));

    for (int i = 0; i < 2001; i++) {
        if (hash1[i] == 1 && hash2[i] == 0) {
            result[0][(*returnColumnSizes)[0]++] = i - 1000;
        }
        if (hash2[i] == 1 && hash1[i] == 0) {
            result[1][(*returnColumnSizes)[1]++] = i - 1000;
        }
    }

    *returnSize = 2;
    return result;      
}
