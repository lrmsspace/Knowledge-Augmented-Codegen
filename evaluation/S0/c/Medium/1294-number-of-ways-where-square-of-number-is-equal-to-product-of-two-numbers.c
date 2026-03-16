// Source: https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given two arrays of integers nums1 and nums2, return the number of triplets formed (type 1 and type 2) under the following rules:
//
//
// 	Type 1: Triplet (i, j, k) if nums1[i]2 == nums2[j] * nums2[k] where 0 <= i < nums1.length and 0 <= j < k < nums2.length.
// 	Type 2: Triplet (i, j, k) if nums2[i]2 == nums1[j] * nums1[k] where 0 <= i < nums2.length and 0 <= j < k < nums1.length.
//
// Example:
// Input: nums1 = [7,4], nums2 = [5,2,8,9]
// Output: 1
// Explanation: Type 1: (1, 1, 2), nums1[1]2 = nums2[1] * nums2[2]. (42 = 2 * 8).
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	1 <= nums1[i], nums2[i] <= 105
//

int numTriplets(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int count = 0;
    for (int i = 0; i < nums1Size; i++) {
        long long square = (long long)nums1[i] * nums1[i];
        for (int j = 0; j < nums2Size; j++) {
            for (int k = j + 1; k < nums2Size; k++) {
                if ((long long)nums2[j] * nums2[k] == square) {
                    count++;
                }
            }
        }
    }
    for (int i = 0; i < nums2Size; i++) {
        long long square = (long long)nums2[i] * nums2[i];
        for (int j = 0; j < nums1Size; j++) {
            for (int k = j + 1; k < nums1Size; k++) {
                if ((long long)nums1[j] * nums1[k] == square) {
                    count++;
                }
            }
        }
    }
    return count;       
}
