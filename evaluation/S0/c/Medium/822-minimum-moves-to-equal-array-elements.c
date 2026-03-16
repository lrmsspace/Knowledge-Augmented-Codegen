// Source: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.
//
// In one move, you can increment n - 1 elements of the array by 1.
//
// Example:
// Input: nums = [1,2,3]
// Output: 3
// Explanation: Only three moves are needed (remember each move increments two elements):
// [1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
//
// Constraints:
// n == nums.length
// 	1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	The answer is guaranteed to fit in a 32-bit integer.
//

int minMoves(int* nums, int numsSize) {
    int min = nums[0];
    long long sum = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
        sum += nums[i];
    }
    
    return (int)(sum - (long long)min * numsSize);      
}
