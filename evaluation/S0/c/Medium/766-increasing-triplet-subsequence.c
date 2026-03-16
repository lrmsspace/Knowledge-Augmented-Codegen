// Source: https://leetcode.com/problems/increasing-triplet-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: true
// Explanation: Any triplet where i < j < k is valid.
//
// Constraints:
// 1 <= nums.length <= 5 * 105
// 	-231 <= nums[i] <= 231 - 1
//
//
//  
// Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
//

bool increasingTriplet(int* nums, int numsSize) {
    int first = __INT_MAX__, second = __INT_MAX__;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] <= first) {
            first = nums[i];
        } else if (nums[i] <= second) {
            second = nums[i];
        } else {
            return true;
        }
    }
    return false;       
}
