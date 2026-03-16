// Source: https://leetcode.com/problems/number-of-subarrays-with-and-value-of-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of subarrays of nums where the bitwise AND of the elements of the subarray equals k.
//
// Example:
// Input: nums = [1,1,1], k = 1
//
// Output: 6
//
// Explanation:
//
// All subarrays contain only 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i], k <= 109
//

class Solution {
    public long countSubarrays(int[] nums, int k) {
        long result = 0;
        int n = nums.length;
        int left = 0;

        while (left < n) {
            if ((nums[left] & k) != k) {
                left++;
                continue;
            }

            int right = left;
            long totalSubarrays = 0;
            long validSubarrays = 0;

            while (right < n && (nums[right] & k) == k) {
                totalSubarrays++;
                if (nums[right] == k) {
                    validSubarrays++;
                }
                right++;
            }

            result += validSubarrays * (validSubarrays + 1) / 2;
            result += validSubarrays * (totalSubarrays - validSubarrays);

            left = right;
        }

        return result;          
    }
}
