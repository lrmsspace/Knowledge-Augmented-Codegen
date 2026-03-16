// Source: https://leetcode.com/problems/partition-array-into-disjoint-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, partition it into two (contiguous) subarrays left and right so that:
//
//
// 	Every element in left is less than or equal to every element in right.
// 	left and right are non-empty.
// 	left has the smallest possible size.
//
//
// Return the length of left after such a partitioning.
//
// Test cases are generated such that partitioning exists.
//
// Example:
// Input: nums = [5,0,3,8,6]
// Output: 3
// Explanation: left = [5,0,3], right = [8,6]
//
// Constraints:
// 2 <= nums.length <= 105
// 	0 <= nums[i] <= 106
// 	There is at least one valid answer for the given input.
//

int partitionDisjoint(int* nums, int numsSize) {
    int leftMax = nums[0];
    int overallMax = nums[0];
    int partitionIndex = 0;

    for (int i = 1; i < numsSize; i++) {
        overallMax = overallMax > nums[i] ? overallMax : nums[i];

        if (nums[i] < leftMax) {
            leftMax = overallMax;
            partitionIndex = i;
        }
    }

    return partitionIndex + 1;      
}
