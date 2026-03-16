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

long long maxAlternatingSum(int* nums, int numsSize){


    long long even_sum = 0;
    long long odd_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        long long new_even_sum = even_sum > odd_sum + nums[i] ? even_sum : odd_sum + nums[i];
        long long new_odd_sum = odd_sum > even_sum - nums[i] ? odd_sum : even_sum - nums[i];
        even_sum = new_even_sum;
        odd_sum = new_odd_sum;
    }
    return even_sum;
}
