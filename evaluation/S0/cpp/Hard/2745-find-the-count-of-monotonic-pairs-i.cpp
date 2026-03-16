// Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
//
//
// 	The lengths of both arrays are n.
// 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
// 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
// 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
//
//
// Return the count of monotonic pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,2]
//
// Output: 4
//
// Explanation:
//
// The good pairs are:
//
//
// 	([0, 1, 1], [2, 2, 1])
// 	([0, 1, 2], [2, 2, 0])
// 	([0, 2, 2], [2, 1, 0])
// 	([1, 2, 2], [1, 1, 0])
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	1 <= nums[i] <= 50
//

class Solution {
public:
    int countOfPairs(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<vector<int>> dpInc(n + 1, vector<int>(51, 0));
        vector<vector<int>> dpDec(n + 1, vector<int>(51, 0));
        
        // Base case
        for (int v = 0; v <= nums[0]; v++) {
            dpInc[1][v] = 1;
            dpDec[1][nums[0] - v] = 1;
        }
        
        // Fill dpInc
        for (int i = 2; i <= n; i++) {
            for (int v = 0; v <= nums[i - 1]; v++) {
                for (int pv = 0; pv <= v; pv++) {
                    dpInc[i][v] = (dpInc[i][v] + dpInc[i - 1][pv]) % MOD;
                }
            }
        }
        
        // Fill dpDec
        for (int i = 2; i <= n; i++) {
            for (int v = 0; v <= nums[i - 1]; v++) {
                for (int pv = v; pv <= nums[i - 1]; pv++) {
                    dpDec[i][v] = (dpDec[i][v] + dpDec[i - 1][pv]) % MOD;
                }
            }
        }
        
        // Calculate result
        int result = 0;
        for (int v = 0; v <= 50; v++) {
            result = (result + (long long)dpInc[n][v] * dpDec[n][v]) % MOD;
        }
        
        return result;          
    }
};
