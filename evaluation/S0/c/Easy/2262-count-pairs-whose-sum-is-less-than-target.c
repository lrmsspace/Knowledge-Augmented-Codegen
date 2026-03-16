// Source: https://leetcode.com/problems/count-pairs-whose-sum-is-less-than-target/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed integer array nums of length n and an integer target, return the number of pairs (i, j) where 0 <= i < j < n and nums[i] + nums[j] < target.
//
// Example:
// Input: nums = [-1,1,2,3,1], target = 2
// Output: 3
// Explanation: There are 3 pairs of indices that satisfy the conditions in the statement:
// - (0, 1) since 0 < 1 and nums[0] + nums[1] = 0 < target
// - (0, 2) since 0 < 2 and nums[0] + nums[2] = 1 < target 
// - (0, 4) since 0 < 4 and nums[0] + nums[4] = 0 < target
// Note that (0, 3) is not counted since nums[0] + nums[3] is not strictly less than the target.
//
// Constraints:
// 1 <= nums.length == n <= 50
// 	-50 <= nums[i], target <= 50
//

int countPairs(int* nums, int numsSize, int target) {
    int count = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] < target) {
                count++;
            }
        }
    }
    return count;       
}
