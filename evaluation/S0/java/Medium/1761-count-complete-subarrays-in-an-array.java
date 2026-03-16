// Source: https://leetcode.com/problems/count-complete-subarrays-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// We call a subarray of an array complete if the following condition is satisfied:
//
//
// 	The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
//
//
// Return the number of complete subarrays.
//
// A subarray is a contiguous non-empty part of an array.
//
// Example:
// Input: nums = [1,3,1,2,2]
// Output: 4
// Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 2000
//

class Solution {
    public int countCompleteSubarrays(int[] nums) {
        int n = nums.length;
        Set<Integer> distinctElements = new HashSet<>();
        for (int num : nums) {
            distinctElements.add(num);
        }
        int totalDistinctCount = distinctElements.size();
        int completeSubarrayCount = 0;

        for (int start = 0; start < n; start++) {
            Set<Integer> currentDistinctElements = new HashSet<>();
            for (int end = start; end < n; end++) {
                currentDistinctElements.add(nums[end]);
                if (currentDistinctElements.size() == totalDistinctCount) {
                    completeSubarrayCount++;
                }
            }
        }

        return completeSubarrayCount;           
    }
}
