// Source: https://leetcode.com/problems/third-maximum-number/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.
//
// Example:
// Input: nums = [3,2,1]
// Output: 1
// Explanation:
// The first distinct maximum is 3.
// The second distinct maximum is 2.
// The third distinct maximum is 1.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-231 <= nums[i] <= 231 - 1
//
//
//  
// Follow up: Can you find an O(n) solution?
//

int thirdMax(int* nums, int numsSize) {
    long max1 = LONG_MIN, max2 = LONG_MIN, max3 = LONG_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max1) {
            max3 = max2;
            max2 = max1;
            max1 = nums[i];
        } else if (nums[i] < max1 && nums[i] > max2) {
            max3 = max2;
            max2 = nums[i];
        } else if (nums[i] < max2 && nums[i] > max3) {
            max3 = nums[i];
        }
    }
    return (max3 == LONG_MIN) ? max1 : max3;        
}
