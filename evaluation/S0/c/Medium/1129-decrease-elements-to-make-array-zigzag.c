// Source: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
//
// An array A is a zigzag array if either:
//
//
//  Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
//  OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
//
//
// Return the minimum number of moves to transform the given array nums into a zigzag array.
//
// Example:
// Input: nums = [1,2,3]
// Output: 2
// Explanation: We can decrease 2 to 0 or 3 to 1.
//
// Constraints:
// 1 <= nums.length <= 1000
//  1 <= nums[i] <= 1000
//

int movesToMakeZigzag(int* nums, int numsSize) {
    int even_moves = 0;
    int odd_moves = 0;

    for (int i = 0; i < numsSize; i++) {
        int left = (i > 0) ? nums[i - 1] : INT_MAX;
        int right = (i < numsSize - 1) ? nums[i + 1] : INT_MAX;
        int decrease_to = (left < right ? left : right) - 1;

        if (i % 2 == 0) {
            if (nums[i] >= decrease_to) {
                even_moves += nums[i] - decrease_to;
            }
        } else {
            if (nums[i] >= decrease_to) {
                odd_moves += nums[i] - decrease_to;
            }
        }
    }

    return (even_moves < odd_moves) ? even_moves : odd_moves;       
}
