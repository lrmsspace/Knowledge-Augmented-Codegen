// Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// The distinct count of a subarray of nums is defined as:
//
//
// 	Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
//
//
// Return the sum of the squares of distinct counts of all subarrays of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,1]
// Output: 15
// Explanation: Six possible subarrays are:
// [1]: 1 distinct value
// [2]: 1 distinct value
// [1]: 1 distinct value
// [1,2]: 2 distinct values
// [2,1]: 2 distinct values
// [1,2,1]: 2 distinct values
// The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<int> lastPos(100001, -1);
        long long result = 0;
        long long currentSum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            int num = nums[right];
            if (lastPos[num] >= left) {
                // Remove contributions from the left side
                for (int i = left; i <= lastPos[num]; ++i) {
                    currentSum -= (right - i);
                    currentSum = (currentSum + MOD) % MOD;
                }
                left = lastPos[num] + 1;
            }
            // Add contributions from the new element
            for (int i = left; i <= right; ++i) {
                currentSum += (right - i + 1);
                currentSum %= MOD;
            }
            lastPos[num] = right;
            result = (result + currentSum) % MOD;
        }

        return result;          
    }
};
