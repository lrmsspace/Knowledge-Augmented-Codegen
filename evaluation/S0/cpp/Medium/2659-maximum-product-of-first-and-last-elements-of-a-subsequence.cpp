// Source: https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer m.
//
// Return the maximum product of the first and last elements of any subsequence of nums of size m.
//
// Example:
// Input: nums = [-1,-9,2,3,-2,-3,1], m = 1
//
// Output: 81
//
// Explanation:
//
// The subsequence [-9] has the largest product of the first and last elements: -9 * -9 = 81. Therefore, the answer is 81.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
// 	1 <= m <= nums.length
//

class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        sort(nums.begin(), nums.end());
        long long prod1 = (long long)nums[0] * nums[m - 1];
        long long prod2 = (long long)nums[nums.size() - m] * nums[nums.size() - 1];
        return max(prod1, prod2);           
    }
};
