// Source: https://leetcode.com/problems/find-the-duplicate-number/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.
//
// There is only one repeated number in nums, return this repeated number.
//
// You must solve the problem without modifying the array nums and using only constant extra space.
//
// Example:
// Input: nums = [1,3,4,2,2]
// Output: 2
//
// Constraints:
// 1 <= n <= 105
// 	nums.length == n + 1
// 	1 <= nums[i] <= n
// 	All the integers in nums appear only once except for precisely one integer which appears two or more times.
//
//
//  
// Follow up:
//
//
// 	How can we prove that at least one duplicate number must exist in nums?
// 	Can you solve the problem in linear runtime complexity?
//

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int tortoise = nums[0];
        int hare = nums[0];

        // Phase 1: Finding the intersection point of the two runners.
        do {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        } while (tortoise != hare);

        // Phase 2: Finding the entrance to the cycle.
        tortoise = nums[0];
        while (tortoise != hare) {
            tortoise = nums[tortoise];
            hare = nums[hare];
        }

        return hare;            
    }
};
