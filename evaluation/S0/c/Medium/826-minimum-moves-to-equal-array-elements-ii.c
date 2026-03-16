// Source: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.
//
// In one move, you can increment or decrement an element of the array by 1.
//
// Test cases are designed so that the answer will fit in a 32-bit integer.
//
// Example:
// Input: nums = [1,2,3]
// Output: 2
// Explanation:
// Only two moves are needed (remember each move increments or decrements one element):
// [1,2,3]  =>  [2,2,3]  =>  [2,2,2]
//
// Constraints:
// n == nums.length
// 	1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

int minMoves2(int* nums, int numsSize) {
    // Helper function to compare two integers (used for qsort)
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }

    // Sort the array to find the median
    qsort(nums, numsSize, sizeof(int), compare);

    // Find the median
    int median = nums[numsSize / 2];

    // Calculate the total moves required to make all elements equal to the median
    int totalMoves = 0;
    for (int i = 0; i < numsSize; i++) {
        totalMoves += abs(nums[i] - median);
    }

    return totalMoves;      
}
