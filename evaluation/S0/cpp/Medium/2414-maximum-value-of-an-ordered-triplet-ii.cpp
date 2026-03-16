// Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such triplets have a negative value, return 0.
//
// The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
//
// Example:
// Input: nums = [12,6,1,2,7]
// Output: 77
// Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
// It can be shown that there are no ordered triplets of indices with a value greater than 77.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();
        long long maxVal = 0;
        long long maxSuffix = nums[n - 1];
        long long maxDiff = 0;

        for (int j = n - 2; j >= 1; --j) {
            maxVal = max(maxVal, maxDiff * nums[j]);
            maxDiff = max(maxDiff, (long long)(nums[j] - nums[0]));
            maxSuffix = max(maxSuffix, (long long)nums[j]);
        }

        return maxVal;          
    }
};
