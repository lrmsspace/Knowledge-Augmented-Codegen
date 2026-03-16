// Source: https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, your goal is to make all elements in nums equal. To complete one operation, follow these steps:
//
//
// 	Find the largest value in nums. Let its index be i (0-indexed) and its value be largest. If there are multiple elements with the largest value, pick the smallest i.
// 	Find the next largest value in nums strictly smaller than largest. Let its value be nextLargest.
// 	Reduce nums[i] to nextLargest.
//
//
// Return the number of operations to make all elements in nums equal.
//
// Example:
// Input: nums = [5,1,3]
// Output: 3
// Explanation: It takes 3 operations to make all elements in nums equal:
// 1. largest = 5 at index 0. nextLargest = 3. Reduce nums[0] to 3. nums = [3,1,3].
// 2. largest = 3 at index 0. nextLargest = 1. Reduce nums[0] to 1. nums = [1,1,3].
// 3. largest = 3 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums = [1,1,1].
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= nums[i] <= 5 * 104
//

class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int operations = 0;
        int n = nums.size();
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                operations += (n - 1 - i);
            }
        }
        return operations;          
    }
};
