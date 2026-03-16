// Source: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of all the arithmetic subsequences of nums.
//
// A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
//
//
// 	For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
// 	For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// The test cases are generated so that the answer fits in 32-bit integer.
//
// Example:
// Input: nums = [2,4,6,8,10]
// Output: 7
// Explanation: All arithmetic subsequence slices are:
// [2,4,6]
// [4,6,8]
// [6,8,10]
// [2,4,6,8]
// [4,6,8,10]
// [2,4,6,8,10]
// [2,6,10]
//
// Constraints:
// 1  <= nums.length <= 1000
// 	-231 <= nums[i] <= 231 - 1
//

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        vector<unordered_map<long long, int>> dp(n);
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                long long diff = (long long)nums[i] - (long long)nums[j];
                
                int countAtJ = dp[j].count(diff) ? dp[j][diff] : 0;
                dp[i][diff] += countAtJ + 1;
                
                result += countAtJ;  // only count sequences of length >= 3
            }
        }
        
        return result;          
    }
};
