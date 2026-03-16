// Source: https://leetcode.com/problems/minimum-array-length-after-pair-removals/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array num sorted in non-decreasing order.
//
// You can perform the following operation any number of times:
//
//
// 	Choose two indices, i and j, where nums[i] < nums[j].
// 	Then, remove the elements at indices i and j from nums. The remaining elements retain their original order, and the array is re-indexed.
//
//
// Return the minimum length of nums after applying the operation zero or more times.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 0
//
// Explanation:
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums is sorted in non-decreasing order.
//

class Solution {
    public int minLengthAfterRemovals(List<Integer> nums) {
        int n = nums.size();
        int left = 0, right = n / 2, pairs = 0;

        while (left < n / 2 && right < n) {
            if (nums.get(left) * 2 <= nums.get(right)) {
                pairs++;
                left++;
            }
            right++;
        }

        return n - pairs * 2;           
    }
}
