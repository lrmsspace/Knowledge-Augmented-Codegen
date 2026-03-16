// Source: https://leetcode.com/problems/find-triangular-sum-of-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums, where nums[i] is a digit between 0 and 9 (inclusive).
//
// The triangular sum of nums is the value of the only element present in nums after the following process terminates:
//
//
// 	Let nums comprise of n elements. If n == 1, end the process. Otherwise, create a new 0-indexed integer array newNums of length n - 1.
// 	For each index i, where 0 <= i < n - 1, assign the value of newNums[i] as (nums[i] + nums[i+1]) % 10, where % denotes modulo operator.
// 	Replace the array nums with newNums.
// 	Repeat the entire process starting from step 1.
//
//
// Return the triangular sum of nums.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: 8
// Explanation:
// The above diagram depicts the process from which we obtain the triangular sum of the array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] <= 9
//

class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> comb(n, 0);
        comb[0] = 1;

        // Precompute binomial coefficients modulo 10
        for (int i = 1; i < n; ++i) {
            comb[i] = 1;
            for (int j = i - 1; j > 0; --j) {
                comb[j] = (comb[j] + comb[j - 1]) % 10;
            }
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            result = (result + nums[i] * comb[n - 1 - i]) % 10;
        }

        return result;          
    }
};
