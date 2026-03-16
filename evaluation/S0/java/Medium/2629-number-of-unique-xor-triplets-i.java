// Source: https://leetcode.com/problems/number-of-unique-xor-triplets-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n, where nums is a permutation of the numbers in the range [1, n].
//
// A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
//
// Return the number of unique XOR triplet values from all possible triplets (i, j, k).
//
// Example:
// Input: nums = [1,2]
//
// Output: 2
//
// Explanation:
//
// The possible XOR triplet values are:
//
//
// 	(0, 0, 0) → 1 XOR 1 XOR 1 = 1
// 	(0, 0, 1) → 1 XOR 1 XOR 2 = 2
// 	(0, 1, 1) → 1 XOR 2 XOR 2 = 1
// 	(1, 1, 1) → 2 XOR 2 XOR 2 = 2
//
//
// The unique XOR values are {1, 2}, so the output is 2.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= n
// 	nums is a permutation of integers from 1 to n.
//

class Solution {
    public int uniqueXorTriplets(int[] nums) {
        int n = nums.length;
        // The maximum possible XOR value for numbers in the range [1, n]
        int maxXorValue = 0;
        for (int i = 1; i <= n; i++) {
            maxXorValue ^= i;
        }

        boolean[] seen = new boolean[maxXorValue + 1];
        int uniqueCount = 0;

        // Iterate through all possible triplets (i, j, k)
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                for (int k = j; k < n; k++) {
                    int xorValue = nums[i] ^ nums[j] ^ nums[k];
                    if (!seen[xorValue]) {
                        seen[xorValue] = true;
                        uniqueCount++;
                    }
                }
            }
        }

        return uniqueCount;         
    }
}
