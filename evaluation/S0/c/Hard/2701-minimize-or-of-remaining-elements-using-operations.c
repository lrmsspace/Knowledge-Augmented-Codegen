// Source: https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// In one operation, you can pick any index i of nums such that 0 <= i < nums.length - 1 and replace nums[i] and nums[i + 1] with a single occurrence of nums[i] & nums[i + 1], where & represents the bitwise AND operator.
//
// Return the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
//
// Example:
// Input: nums = [3,5,3,2,7], k = 2
// Output: 3
// Explanation: Let's do the following operations:
// 1. Replace nums[0] and nums[1] with (nums[0] & nums[1]) so that nums becomes equal to [1,3,2,7].
// 2. Replace nums[2] and nums[3] with (nums[2] & nums[3]) so that nums becomes equal to [1,3,2].
// The bitwise-or of the final array is 3.
// It can be shown that 3 is the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < 230
// 	0 <= k < nums.length
//

int minOrAfterOperations(int* nums, int numsSize, int k) {
    int left = 0, right = (1 << 30) - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int ops = 0;
        int curr_and = -1; // all bits set
        for (int i = 0; i < numsSize; ++i) {
            curr_and &= nums[i];
            if ((curr_and | mid) == mid) {
                // can form a segment ending here
                ops++;
                curr_and = -1; // reset for next segment
            }
        }
        if (ops >= numsSize - k) {
            // can achieve with mid
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;        
}
