// Source: https://leetcode.com/problems/power-of-heroes/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the strength of some heroes. The power of a group of heroes is defined as follows:
//
//
// 	Let i0, i1, ... ,ik be the indices of the heroes in a group. Then, the power of this group is max(nums[i0], nums[i1], ... ,nums[ik])2 * min(nums[i0], nums[i1], ... ,nums[ik]).
//
//
// Return the sum of the power of all non-empty groups of heroes possible. Since the sum could be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,1,4]
// Output: 141
// Explanation: 
// 1st group: [2] has power = 22 * 2 = 8.
// 2nd group: [1] has power = 12 * 1 = 1. 
// 3rd group: [4] has power = 42 * 4 = 64. 
// 4th group: [2,1] has power = 22 * 1 = 4. 
// 5th group: [2,4] has power = 42 * 2 = 32. 
// 6th group: [1,4] has power = 42 * 1 = 16. 
// ​​​​​​​7th group: [2,1,4] has power = 42​​​​​​​ * 1 = 16. 
// The sum of powers of all groups is 8 + 1 + 64 + 4 + 32 + 16 + 16 = 141.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int sumOfPower(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        sort(nums.begin(), nums.end());
        long long result = 0;
        long long suffixSum = 0;
        
        for (int i = nums.size() - 1; i >= 0; i--) {
            long long maxVal = nums[i];
            long long minVal = nums[i];
            suffixSum = (suffixSum * 2 + maxVal) % MOD;
            long long power = (maxVal * maxVal) % MOD;
            result = (result + power * suffixSum) % MOD;
        }
        
        return (int)result;         
    }
};
