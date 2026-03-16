// Source: https://leetcode.com/problems/maximum-alternating-subsequence-sum/   |   Difficulty: Medium
//
// Problem Description:
// The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the sum of the elements at odd indices.
//
//
// 	For example, the alternating sum of [4,2,5,3] is (4 + 5) - (2 + 3) = 4.
//
//
// Given an array nums, return the maximum alternating sum of any subsequence of nums (after reindexing the elements of the subsequence).
//
//
//
//
// A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
//
// Example:
// Input: nums = [4,2,5,3]
// Output: 7
// Explanation: It is optimal to choose the subsequence [4,2,5] with alternating sum (4 + 5) - 2 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {

    public long maxAlternatingSum(int[] nums) {

        
        long evenSum = nums[0];
        long oddSum = 0;

        for (int i = 1; i < nums.length; i++) {
            long newEvenSum = Math.max(evenSum, oddSum + nums[i]);
            long newOddSum = Math.max(oddSum, evenSum - nums[i]);

            evenSum = newEvenSum;
            oddSum = newOddSum;
        }

        return evenSum;
    }

}
