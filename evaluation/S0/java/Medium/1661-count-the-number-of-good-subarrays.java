// Source: https://leetcode.com/problems/count-the-number-of-good-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of good subarrays of nums.
//
// A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,1,1,1,1], k = 10
// Output: 1
// Explanation: The only good subarray is the array nums itself.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 109
//

class Solution {
    public long countGood(int[] nums, int k) {
        long count = 0;
        long result = 0;
        int left = 0;
        int n = nums.length;
        int[] freq = new int[100001];

        for (int right = 0; right < n; right++) {
            count += freq[nums[right]];
            freq[nums[right]]++;

            while (count >= k) {
                result += n - right;
                freq[nums[left]]--;
                count -= freq[nums[left]];
                left++;
            }
        }

        return result;          
    }
}
