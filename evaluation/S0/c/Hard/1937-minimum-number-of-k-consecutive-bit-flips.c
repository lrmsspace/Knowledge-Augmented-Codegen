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

int minKBitFlips(int* nums, int numsSize, int k) {
    int flipCount = 0;
    int currentFlips = 0;
    int *isFlipped = (int*)calloc(numsSize, sizeof(int));
    if (!isFlipped) return -1; /* allocation failure */

    for (int i = 0; i < numsSize; i++) {
        if (i >= k) {
            currentFlips ^= isFlipped[i - k];
        }
        if ((nums[i] ^ currentFlips) == 0) {
            if (i + k > numsSize) {
                free(isFlipped);
                return -1; /* not enough space to flip */
            }
            isFlipped[i] = 1;
            currentFlips ^= 1;
            flipCount++;
        }
    }

    free(isFlipped);
    return flipCount;       
}
