// Source: https://leetcode.com/problems/count-alternating-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// We call a subarray alternating if no two adjacent elements in the subarray have the same value.
//
// Return the number of alternating subarrays in nums.
//
// Example:
// Input: nums = [0,1,1,1]
//
// Output: 5
//
// Explanation:
//
// The following subarrays are alternating: [0], [1], [1], [1], and [0,1].
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

class Solution {
    public long countAlternatingSubarrays(int[] nums) {
        long count = 0;
        int n = nums.length;
        int length = 1;

        for (int i = 0; i < n; i++) {
            count++; // Count single element subarray

            if (i > 0 && nums[i] != nums[i - 1]) {
                length++;
            } else {
                length = 1;
            }

            count += length - 1; // Count subarrays ending at index i
        }

        return count;           
    }
}
