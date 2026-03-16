// Source: https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.
//
// Return any such subsequence as an integer array of length k.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [2,1,3,3], k = 2
// Output: [3,3]
// Explanation:
// The subsequence has the largest sum of 3 + 3 = 6.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-105 <= nums[i] <= 105
// 	1 <= k <= nums.length
//

class Solution {
    public int[] maxSubsequence(int[] nums, int k) {
        int n = nums.length;
        int[] sorted = nums.clone();
        Arrays.sort(sorted);
        int threshold = sorted[n - k];

        int count = 0;
        for (int num : nums) {
            if (num > threshold) {
                count++;
            }
        }

        int[] result = new int[k];
        int index = 0;
        for (int num : nums) {
            if (num > threshold) {
                result[index++] = num;
            } else if (num == threshold && count < k) {
                result[index++] = num;
                count++;
            }
            if (index == k) {
                break;
            }
        }

        return result;          
    }
}
