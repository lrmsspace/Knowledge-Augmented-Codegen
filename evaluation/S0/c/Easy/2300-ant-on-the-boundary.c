// Source: https://leetcode.com/problems/ant-on-the-boundary/   |   Difficulty: Easy
//
// Problem Description:
// An ant is on a boundary. It sometimes goes left and sometimes right.
//
// You are given an array of non-zero integers nums. The ant starts reading nums from the first element of it to its end. At each step, it moves according to the value of the current element:
//
//
// 	If nums[i] < 0, it moves left by -nums[i] units.
// 	If nums[i] > 0, it moves right by nums[i] units.
//
//
// Return the number of times the ant returns to the boundary.
//
// Example:
// Input: nums = [2,3,-5]
// Output: 1
// Explanation: After the first step, the ant is 2 steps to the right of the boundary.
// After the second step, the ant is 5 steps to the right of the boundary.
// After the third step, the ant is on the boundary.
// So the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-10 <= nums[i] <= 10
// 	nums[i] != 0
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int returnToBoundaryCount(int* nums, int numsSize) {
    int position = 0;
    int returnCount = 0;

    for (int i = 0; i < numsSize; i++) {
        position += nums[i];
        if (position == 0) {
            returnCount++;
        }
    }

    return returnCount;     
}
