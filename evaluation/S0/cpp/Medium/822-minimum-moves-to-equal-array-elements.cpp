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

class Solution {
public:
    int minMoves(vector<int>& nums) {
        long long total = 0;
        int minNum = INT_MAX;
        for (int num : nums) {
            total += num;
            minNum = min(minNum, num);
        }
        return total - (long long)minNum * nums.size();         
    }
};
