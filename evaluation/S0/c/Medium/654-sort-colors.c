// Source: https://leetcode.com/problems/sort-colors/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
//
// We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
//
// You must solve this problem without using the library's sort function.
//
// Example:
// Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]
//
// Constraints:
// n == nums.length
// 	1 <= n <= 300
// 	nums[i] is either 0, 1, or 2.
//
//
//  
// Follow up: Could you come up with a one-pass algorithm using only constant extra space?
//

void sortColors(int* nums, int numsSize) {
    int low = 0, mid = 0, high = numsSize - 1;
    int temp;

    while (mid <= high) {
        if (nums[mid] == 0) {
            // Swap nums[low] and nums[mid]
            temp = nums[low];
            nums[low] = nums[mid];
            nums[mid] = temp;
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else { // nums[mid] == 2
            // Swap nums[mid] and nums[high]
            temp = nums[mid];
            nums[mid] = nums[high];
            nums[high] = temp;
            high--;
        }
    }       
}
