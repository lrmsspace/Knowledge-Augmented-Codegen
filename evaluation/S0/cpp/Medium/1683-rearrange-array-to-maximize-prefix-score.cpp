// Source: https://leetcode.com/problems/rearrange-array-to-maximize-prefix-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. You can rearrange the elements of nums to any order (including the given order).
//
// Let prefix be the array containing the prefix sums of nums after rearranging it. In other words, prefix[i] is the sum of the elements from 0 to i in nums after rearranging it. The score of nums is the number of positive integers in the array prefix.
//
// Return the maximum score you can achieve.
//
// Example:
// Input: nums = [2,-1,0,1,-3,3,-3]
// Output: 6
// Explanation: We can rearrange the array into nums = [2,3,1,-1,-3,0,-3].
// prefix = [2,5,6,5,2,2,-1], so the score is 6.
// It can be shown that 6 is the maximum score we can obtain.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-106 <= nums[i] <= 106
//

class Solution {
public:
    int maxScore(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int score = 0;
        long long prefixSum = 0;
        for (int num : nums) {
            prefixSum += num;
            if (prefixSum > 0) {
                score++;
            } else {
                break;
            }
        }
        return score;           
    }
};
