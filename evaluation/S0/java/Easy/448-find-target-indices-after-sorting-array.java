// Source: https://leetcode.com/problems/find-target-indices-after-sorting-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums and a target element target.
//
// A target index is an index i such that nums[i] == target.
//
// Return a list of the target indices of nums after sorting nums in non-decreasing order. If there are no target indices, return an empty list. The returned list must be sorted in increasing order.
//
// Example:
// Input: nums = [1,2,5,2,3], target = 2
// Output: [1,2]
// Explanation: After sorting, nums is [1,2,2,3,5].
// The indices where nums[i] == 2 are 1 and 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i], target <= 100
//

class Solution {
    public List<Integer> targetIndices(int[] nums, int target) {
        List<Integer> result = new ArrayList<>();
        Arrays.sort(nums);
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == target) {
                result.add(i);
            }
        }
        return result;          
    }
}
