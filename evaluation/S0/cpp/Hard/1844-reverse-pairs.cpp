// Source: https://leetcode.com/problems/reverse-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of reverse pairs in the array.
//
// A reverse pair is a pair (i, j) where:
//
//
// 	0 <= i < j < nums.length and
// 	nums[i] > 2 * nums[j].
//
// Example:
// Input: nums = [1,3,2,3,1]
// Output: 2
// Explanation: The reverse pairs are:
// (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
// (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-231 <= nums[i] <= 231 - 1
//

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);         
    }
};
