// Source: https://leetcode.com/problems/132-pattern/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
//
// Return true if there is a 132 pattern in nums, otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: false
// Explanation: There is no 132 pattern in the sequence.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 2 * 105
// 	-109 <= nums[i] <= 109
//

bool find132pattern(int* nums, int numsSize) {
    int stack[numsSize];
    int top = -1;
    int third = -2147483648; // Represents the '2' in the '132' pattern

    for (int i = numsSize - 1; i >= 0; i--) {
        if (nums[i] < third) {
            return true; // Found a valid '1' in the '132' pattern
        }
        while (top >= 0 && nums[i] > stack[top]) {
            third = stack[top--]; // Update 'third' to the last popped value
        }
        stack[++top] = nums[i]; // Push current number onto the stack
    }

    return false; // No '132' pattern found     
}
