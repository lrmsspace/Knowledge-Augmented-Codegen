// Source: https://leetcode.com/problems/maximum-length-of-repeated-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.
//
// Example:
// Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
// Output: 3
// Explanation: The repeated subarray with maximum length is [3,2,1].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	0 <= nums1[i], nums2[i] <= 100
//

int findLength(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int maxLength = 0;
    int dp[1001][1001]; // DP table to store lengths of common subarrays

    // Initialize the DP table with zeros
    for (int i = 0; i <= nums1Size; i++) {
        for (int j = 0; j <= nums2Size; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill the DP table
    for (int i = 1; i <= nums1Size; i++) {
        for (int j = 1; j <= nums2Size; j++) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                }
            }
        }
    }

    return maxLength;       
}
