// Source: https://leetcode.com/problems/house-robber-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
//
// Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
//
// Example:
// Input: nums = [2,3,2]
// Output: 3
// Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 1000
//

int rob(int* nums, int numsSize) {
    if (numsSize == 1) {
        return nums[0];
    }

    int rob_linear(int* arr, int size) {
        int prev1 = 0; // max money that can be robbed up to the previous house
        int prev2 = 0; // max money that can be robbed up to the house before the previous one

        for (int i = 0; i < size; i++) {
            int current = arr[i];
            int temp = prev1;
            prev1 = (prev2 + current > prev1) ? prev2 + current : prev1;
            prev2 = temp;
        }

        return prev1;
    }

    // Case 1: Rob houses from index 0 to numsSize - 2
    int max1 = rob_linear(nums, numsSize - 1);
    // Case 2: Rob houses from index 1 to numsSize - 1
    int max2 = rob_linear(nums + 1, numsSize - 1);

    return (max1 > max2) ? max1 : max2;     
}
