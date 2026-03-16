// Source: https://leetcode.com/problems/minimum-increment-to-make-array-unique/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. In one move, you can pick an index i where 0 <= i < nums.length and increment nums[i] by 1.
//
// Return the minimum number of moves to make every value in nums unique.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: nums = [1,2,2]
// Output: 1
// Explanation: After 1 move, the array could be [1, 2, 3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//

int minIncrementForUnique(int* nums, int numsSize) {
    int count[200001] = {0};
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    int moves = 0;
    int taken = 0;

    for (int i = 0; i < 200001; i++) {
        if (count[i] > 1) {
            taken += count[i] - 1;
            moves -= i * (count[i] - 1);
        } else if (taken > 0 && count[i] == 0) {
            taken--;
            moves += i;
        }
    }

    return moves;       
}
