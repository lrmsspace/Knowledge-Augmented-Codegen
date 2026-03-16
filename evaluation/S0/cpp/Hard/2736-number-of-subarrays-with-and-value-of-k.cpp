// Source: https://leetcode.com/problems/number-of-subarrays-with-and-value-of-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of subarrays of nums where the bitwise AND of the elements of the subarray equals k.
//
// Example:
// Input: nums = [1,1,1], k = 1
//
// Output: 6
//
// Explanation:
//
// All subarrays contain only 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i], k <= 109
//

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long result = 0;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            int currentAnd = nums[i];
            if (currentAnd == k) {
                result++;
            }
            for (int j = i + 1; j < n; j++) {
                currentAnd &= nums[j];
                if (currentAnd < k) {
                    break;  // No need to continue, AND will only decrease
                }
                if (currentAnd == k) {
                    result++;
                }
            }
        }
        
        return result;          
    }
};
