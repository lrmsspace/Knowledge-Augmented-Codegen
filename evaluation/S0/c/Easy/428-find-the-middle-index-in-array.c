// Source: https://leetcode.com/problems/find-the-middle-index-in-array/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed integer array nums, find the leftmost middleIndex (i.e., the smallest amongst all the possible ones).
//
// A middleIndex is an index where nums[0] + nums[1] + ... + nums[middleIndex-1] == nums[middleIndex+1] + nums[middleIndex+2] + ... + nums[nums.length-1].
//
// If middleIndex == 0, the left side sum is considered to be 0. Similarly, if middleIndex == nums.length - 1, the right side sum is considered to be 0.
//
// Return the leftmost middleIndex that satisfies the condition, or -1 if there is no such index.
//
// Example:
// Input: nums = [2,3,-1,8,4]
// Output: 3
// Explanation: The sum of the numbers before index 3 is: 2 + 3 + -1 = 4
// The sum of the numbers after index 3 is: 4 = 4
//
// Constraints:
// 1 <= nums.length <= 100
// 	-1000 <= nums[i] <= 1000
//
//
//  
// Note: This question is the same as 724: https://leetcode.com/problems/find-pivot-index/
//

int findMiddleIndex(int* nums, int numsSize) {
    int totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    int leftSum = 0;
    for (int i = 0; i < numsSize; i++) {
        int rightSum = totalSum - leftSum - nums[i];
        if (leftSum == rightSum) {
            return i;
        }
        leftSum += nums[i];
    }

    return -1;      
}
