// Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/   |   Difficulty: Easy
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
// 3 <= nums.length <= 100
// 	1 <= nums[i] <= 106
//

class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        long long max_value = 0;
        int n = nums.size();

        for (int j = 1; j < n - 1; ++j) {
            int max_left = 0;
            for (int i = 0; i < j; ++i) {
                max_left = max(max_left, nums[i]);
            }

            int max_right = 0;
            for (int k = j + 1; k < n; ++k) {
                max_right = max(max_right, nums[k]);
            }

            long long current_value = static_cast<long long>(max_left - nums[j]) * max_right;
            max_value = max(max_value, current_value);
        }

        return max_value;           
    }
};
