// Source: https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// The frequency of an element x is the number of times it occurs in an array.
//
// An array is called good if the frequency of each element in this array is less than or equal to k.
//
// Return the length of the longest good subarray of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3,1,2,3,1,2], k = 2
// Output: 6
// Explanation: The longest possible good subarray is [1,2,3,1,2,3] since the values 1, 2, and 3 occur at most twice in this subarray. Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good.
// It can be shown that there are no good subarrays with length more than 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= nums.length
//

class Solution {
    public int maxSubarrayLength(int[] nums, int k) {
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < nums.length; right++) {
            frequencyMap.put(nums[right], frequencyMap.getOrDefault(nums[right], 0) + 1);

            while (frequencyMap.get(nums[right]) > k) {
                frequencyMap.put(nums[left], frequencyMap.get(nums[left]) - 1);
                left++;
            }

            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;           
    }
}
