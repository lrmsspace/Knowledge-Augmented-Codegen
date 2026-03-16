// Source: https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The value of this array is defined as the sum of |nums[i] - nums[i + 1]| for all 0 <= i < nums.length - 1.
//
// You are allowed to select any subarray of the given array and reverse it. You can perform this operation only once.
//
// Find maximum possible value of the final array.
//
// Example:
// Input: nums = [2,3,1,5,4]
// Output: 10
// Explanation: By reversing the subarray [3,1,5] the array becomes [2,5,1,3,4] whose value is 10.
//
// Constraints:
// 2 <= nums.length <= 3 * 104
// 	-105 <= nums[i] <= 105
// 	The answer is guaranteed to fit in a 32-bit integer.
//

class Solution {
    public int maxValueAfterReverse(int[] nums) {
        int n = nums.length;
        int originalValue = 0;

        for (int i = 0; i < n - 1; i++) {
            originalValue += Math.abs(nums[i] - nums[i + 1]);
        }

        int maxGain = 0;

        for (int i = 1; i < n - 1; i++) {
            int gain1 = Math.abs(nums[0] - nums[i + 1]) - Math.abs(nums[i] - nums[i + 1]);
            int gain2 = Math.abs(nums[n - 1] - nums[i - 1]) - Math.abs(nums[i] - nums[i - 1]);
            maxGain = Math.max(maxGain, Math.max(gain1, gain2));
        }

        int minEdge = Integer.MAX_VALUE;
        int maxEdge = Integer.MIN_VALUE;

        for (int i = 0; i < n - 1; i++) {
            int a = nums[i];
            int b = nums[i + 1];
            minEdge = Math.min(minEdge, Math.min(a, b));
            maxEdge = Math.max(maxEdge, Math.max(a, b));
        }

        int edgeGain = 2 * (maxEdge - minEdge);
        maxGain = Math.max(maxGain, edgeGain);

        return originalValue + maxGain;                 
    }
}
