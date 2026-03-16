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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumXORSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int n = nums1Size;
    int dp[1 << n];
    for (int i = 0; i < (1 << n); ++i) {
        dp[i] = 0x3f3f3f3f; // Initialize with a large number
    }
    dp[0] = 0; // Base case: no elements chosen

    for (int mask = 0; mask < (1 << n); ++mask) {
        int count = __builtin_popcount(mask); // Count of elements chosen from nums2
        if (count >= n) continue; // If we've chosen all elements, skip

        for (int j = 0; j < n; ++j) {
            if ((mask & (1 << j)) == 0) { // If the j-th element of nums2 is not chosen
                int newMask = mask | (1 << j); // Choose the j-th element
                dp[newMask] = dp[newMask] < (dp[mask] + (nums1[count] ^ nums2[j])) ? dp[newMask] : (dp[mask] + (nums1[count] ^ nums2[j]));
            }
        }
    }

    return dp[(1 << n) - 1]; // Return the minimum XOR sum when all elements are chosen     
}
