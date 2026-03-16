// Source: https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary array nums and an integer k.
//
// A k-bit flip is choosing a subarray of length k from nums and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
//
// Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is not possible, return -1.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [0,1,0], k = 1
// Output: 2
// Explanation: Flip nums[0], then flip nums[2].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= k <= nums.length
//

class Solution {
    public int minKBitFlips(int[] nums, int k) {
        int n = nums.length;
        int[] isFlipped = new int[n];
        int flipCount = 0;
        int currentFlips = 0;

        for (int i = 0; i < n; i++) {
            currentFlips ^= isFlipped[i];

            if (nums[i] == currentFlips) {
                if (i + k > n) {
                    return -1;
                }
                flipCount++;
                currentFlips ^= 1;
                if (i + k < n) {
                    isFlipped[i + k] ^= 1;
                }
            }
        }

        return flipCount;                   
    }
}
