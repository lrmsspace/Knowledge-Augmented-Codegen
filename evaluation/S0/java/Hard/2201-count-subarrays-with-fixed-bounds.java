// Source: https://leetcode.com/problems/count-subarrays-with-fixed-bounds/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers minK and maxK.
//
// A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
//
//
// 	The minimum value in the subarray is equal to minK.
// 	The maximum value in the subarray is equal to maxK.
//
//
// Return the number of fixed-bound subarrays.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
// Output: 2
// Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i], minK, maxK <= 106
//

class Solution {
    public long countSubarrays(int[] nums, int minK, int maxK) {
        long result = 0;
        int n = nums.length;

        int lastMinKIndex = -1;
        int lastMaxKIndex = -1;
        int lastInvalidIndex = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] < minK || nums[i] > maxK) {
                lastInvalidIndex = i;
            }
            if (nums[i] == minK) {
                lastMinKIndex = i;
            }
            if (nums[i] == maxK) {
                lastMaxKIndex = i;
            }

            int validStartIndex = Math.min(lastMinKIndex, lastMaxKIndex);
            if (validStartIndex > lastInvalidIndex) {
                result += validStartIndex - lastInvalidIndex;
            }
        }

        return result;          
    }
}
