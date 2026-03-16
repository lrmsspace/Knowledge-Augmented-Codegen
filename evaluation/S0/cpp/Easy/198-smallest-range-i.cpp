// Source: https://leetcode.com/problems/smallest-range-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// In one operation, you can choose any index i where 0 <= i < nums.length and change nums[i] to nums[i] + x where x is an integer from the range [-k, k]. You can apply this operation at most once for each index i.
//
// The score of nums is the difference between the maximum and minimum elements in nums.
//
// Return the minimum score of nums after applying the mentioned operation at most once for each index in it.
//
// Example:
// Input: nums = [1], k = 0
// Output: 0
// Explanation: The score is max(nums) - min(nums) = 1 - 1 = 0.
//
// Constraints:
// 1 <= nums.length <= 104
// 	0 <= nums[i] <= 104
// 	0 <= k <= 104
//

class Solution {
public:
    int smallestRangeI(vector<int>& nums, int k) {
        int maxNum = *max_element(nums.begin(), nums.end());
        int minNum = *min_element(nums.begin(), nums.end());
        return max(0, (maxNum - k) - (minNum + k));         
    }
};
