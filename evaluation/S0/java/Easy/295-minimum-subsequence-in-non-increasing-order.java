// Source: https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/   |   Difficulty: Easy
//
// Problem Description:
// Given the array nums, obtain a subsequence of the array whose sum of elements is strictly greater than the sum of the non included elements in such subsequence. 
//
// If there are multiple solutions, return the subsequence with minimum size and if there still exist multiple solutions, return the subsequence with the maximum total sum of all its elements. A subsequence of an array can be obtained by erasing some (possibly zero) elements from the array. 
//
// Note that the solution with the given constraints is guaranteed to be unique. Also return the answer sorted in non-increasing order.
//
// Example:
// Input: nums = [4,3,10,9,8]
// Output: [10,9] 
// Explanation: The subsequences [10,9] and [10,8] are minimal such that the sum of their elements is strictly greater than the sum of elements not included. However, the subsequence [10,9] has the maximum total sum of its elements.
//
// Constraints:
// 1 <= nums.length <= 500
// 	1 <= nums[i] <= 100
//

class Solution {
    public List<Integer> minSubsequence(int[] nums) {
        Arrays.sort(nums);
        List<Integer> result = new ArrayList<>();
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        int subsequenceSum = 0;
        for (int i = nums.length - 1; i >= 0; i--) {
            subsequenceSum += nums[i];
            result.add(nums[i]);
            if (subsequenceSum > totalSum - subsequenceSum) {
                break;
            }
        }
        return result;          
    }
}
