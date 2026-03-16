// Source: https://leetcode.com/problems/find-closest-number-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums of size n, return the number with the value closest to 0 in nums. If there are multiple answers, return the number with the largest value.
//
// Example:
// Input: nums = [-4,-2,1,4,8]
// Output: 1
// Explanation:
// The distance from -4 to 0 is |-4| = 4.
// The distance from -2 to 0 is |-2| = 2.
// The distance from 1 to 0 is |1| = 1.
// The distance from 4 to 0 is |4| = 4.
// The distance from 8 to 0 is |8| = 8.
// Thus, the closest number to 0 in the array is 1.
//
// Constraints:
// 1 <= n <= 1000
// 	-105 <= nums[i] <= 105
//

int findClosestNumber(int* nums, int numsSize) {
    int closest = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (abs(nums[i]) < abs(closest) || (abs(nums[i]) == abs(closest) && nums[i] > closest)) {
            closest = nums[i];
        }
    }
    return closest;     
}
