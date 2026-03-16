// Source: https://leetcode.com/problems/minimum-numbers-of-function-calls-to-make-target-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You have an integer array arr of the same length with all values set to 0 initially. You also have the following modify function:
//
// You want to use the modify function to convert arr to nums using the minimum number of calls.
//
// Return the minimum number of function calls to make nums from arr.
//
// The test cases are generated so that the answer fits in a 32-bit signed integer.
//
// Example:
// Input: nums = [1,5]
// Output: 5
// Explanation: Increment by 1 (second element): [0, 0] to get [0, 1] (1 operation).
// Double all the elements: [0, 1] -> [0, 2] -> [0, 4] (2 operations).
// Increment by 1 (both elements)  [0, 4] -> [1, 4] -> [1, 5] (2 operations).
// Total of operations: 1 + 2 + 2 = 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//

int minOperations(int* nums, int numsSize) {
    int operations = 0;
    int maxDoublings = 0;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int doublings = 0;

        while (num > 0) {
            if (num % 2 == 1) {
                operations++;  // Increment operation
                num--;
            } else {
                num /= 2;
                doublings++;
            }
        }

        if (doublings > maxDoublings) {
            maxDoublings = doublings;
        }
    }

    operations += maxDoublings;  // Add the maximum number of doublings needed

    return operations;      
}
