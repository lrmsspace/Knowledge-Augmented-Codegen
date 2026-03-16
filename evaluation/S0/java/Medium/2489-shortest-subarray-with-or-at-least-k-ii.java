// Source: https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of non-negative integers and an integer k.
//
// An array is called special if the bitwise OR of all of its elements is at least k.
//
// Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 1
//
// Explanation:
//
// The subarray [3] has OR value of 3. Hence, we return 1.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	0 <= nums[i] <= 109
// 	0 <= k <= 109
//

class Solution {
    public int minimumSubarrayLength(int[] nums, int k) {
        int n = nums.length;
        int minLength = Integer.MAX_VALUE;

        for (int start = 0; start < n; start++) {
            int currentOr = 0;
            for (int end = start; end < n; end++) {
                currentOr |= nums[end];
                if (currentOr >= k) {
                    minLength = Math.min(minLength, end - start + 1);
                    break; // No need to check further as we want the shortest subarray
                }
            }
        }

        return minLength == Integer.MAX_VALUE ? -1 : minLength;         
    }
}
