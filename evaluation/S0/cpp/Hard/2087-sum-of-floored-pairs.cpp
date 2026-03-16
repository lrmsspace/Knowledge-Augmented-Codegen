// Source: https://leetcode.com/problems/sum-of-floored-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for all pairs of indices 0 <= i, j < nums.length in the array. Since the answer may be too large, return it modulo 109 + 7.
//
// The floor() function returns the integer part of the division.
//
// Example:
// Input: nums = [2,5,9]
// Output: 10
// Explanation:
// floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
// floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
// floor(5 / 2) = 2
// floor(9 / 2) = 4
// floor(9 / 5) = 1
// We calculate the floor of the division for every pair of indices in the array then sum them up.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAX_A = 100000;
        vector<int> freq(MAX_A + 1, 0);
        
        // Count frequency of each number
        for (int num : nums) {
            freq[num]++;
        }
        
        // Prefix sum of frequencies
        for (int i = 1; i <= MAX_A; i++) {
            freq[i] += freq[i - 1];
        }
        
        long long result = 0;
        
        // Calculate the sum of floored pairs
        for (int i = 1; i <= MAX_A; i++) {
            if (freq[i] == freq[i - 1]) continue; // No occurrences of i
            
            for (int multiple = i; multiple <= MAX_A; multiple += i) {
                int left = multiple;
                int right = min(multiple + i - 1, MAX_A);
                int countInRange = freq[right] - freq[left - 1];
                
                result = (result + (long long)(i / i) * countInRange * (freq[i] - freq[i - 1])) % MOD;
            }
        }
        
        return (int)result;         
    }
};
