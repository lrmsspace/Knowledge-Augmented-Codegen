// Source: https://leetcode.com/problems/max-consecutive-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary array nums, return the maximum number of consecutive 1's in the array.
//
// Example:
// Input: nums = [1,1,0,1,1,1]
// Output: 3
// Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int maxCount = 0;
    int currentCount = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            currentCount++;
            if (currentCount > maxCount) {
                maxCount = currentCount;
            }
        } else {
            currentCount = 0;
        }
    }

    return maxCount;        
}
