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

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        int median = nums[n / 2];
        long long moves = 0;
        for (int num : nums) {
            moves += abs(num - median);
        }
        return moves;           
    }
};
