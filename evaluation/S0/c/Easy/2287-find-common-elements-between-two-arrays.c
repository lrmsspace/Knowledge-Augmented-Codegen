// Source: https://leetcode.com/problems/find-common-elements-between-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of sizes n and m, respectively. Calculate the following values:
//
//
// 	answer1 : the number of indices i such that nums1[i] exists in nums2.
// 	answer2 : the number of indices i such that nums2[i] exists in nums1.
//
//
// Return [answer1,answer2].
//
// Example:
// Input: nums1 = [2,3,2], nums2 = [1,2]
//
// Output: [2,1]
//
// Explanation:
//
// Constraints:
// n == nums1.length
// 	m == nums2.length
// 	1 <= n, m <= 100
// 	1 <= nums1[i], nums2[i] <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findIntersectionValues(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = 0;
    result[1] = 0;

    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {
                result[0]++;
                break;
            }
        }
    }

    for (int i = 0; i < nums2Size; i++) {
        for (int j = 0; j < nums1Size; j++) {
            if (nums2[i] == nums1[j]) {
                result[1]++;
                break;
            }
        }
    }

    *returnSize = 2;
    return result;      
}
