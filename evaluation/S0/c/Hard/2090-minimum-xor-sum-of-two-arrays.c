// Source: https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of length n.
//
// The XOR sum of the two integer arrays is (nums1[0] XOR nums2[0]) + (nums1[1] XOR nums2[1]) + ... + (nums1[n - 1] XOR nums2[n - 1]) (0-indexed).
//
//
// 	For example, the XOR sum of [1,2,3] and [3,2,1] is equal to (1 XOR 3) + (2 XOR 2) + (3 XOR 1) = 2 + 0 + 2 = 4.
//
//
// Rearrange the elements of nums2 such that the resulting XOR sum is minimized.
//
// Return the XOR sum after the rearrangement.
//
// Example:
// Input: nums1 = [1,2], nums2 = [2,3]
// Output: 2
// Explanation: Rearrange nums2 so that it becomes [3,2].
// The XOR sum is (1 XOR 3) + (2 XOR 2) = 2 + 0 = 2.
//
// Constraints:
// n == nums1.length
// 	n == nums2.length
// 	1 <= n <= 14
// 	0 <= nums1[i], nums2[i] <= 107
//

int minimumXORSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int n = nums1Size;
    int size = 1 << n;
    int *dp = (int*)malloc(size * sizeof(int));
    if (!dp) return -1; /* allocation failure */

    for (int mask = 0; mask < size; ++mask) {
        dp[mask] = __INT_MAX__;
    }
    dp[0] = 0;

    for (int mask = 0; mask < size; ++mask) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) count++;
        }
        for (int j = 0; j < n; ++j) {
            if (!(mask & (1 << j))) {
                int newMask = mask | (1 << j);
                int xorSum = nums1[count] ^ nums2[j];
                if (dp[mask] + xorSum < dp[newMask]) {
                    dp[newMask] = dp[mask] + xorSum;
                }
            }
        }
    }

    int result = dp[size - 1];
    free(dp);
    return result;      
}
