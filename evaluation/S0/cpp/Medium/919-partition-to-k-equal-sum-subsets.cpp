// Source: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.
//
// Example:
// Input: nums = [4,3,2,3,5,2,1], k = 4
// Output: true
// Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	1 <= nums[i] <= 104
// 	The frequency of each element is in the range [1, 4].
//

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) return false;
        int target = total / k;
        sort(nums.rbegin(), nums.rend());
        vector<int> buckets(k, 0);

        function<bool(int)> backtrack = [&](int index) {
            if (index == nums.size()) {
                for (int i = 0; i < k; ++i) {
                    if (buckets[i] != target) return false;
                }
                return true;
            }

            for (int i = 0; i < k; ++i) {
                if (buckets[i] + nums[index] <= target) {
                    buckets[i] += nums[index];
                    if (backtrack(index + 1)) return true;
                    buckets[i] -= nums[index];
                }
                if (buckets[i] == 0) break; // Optimization: avoid redundant work
            }
            return false;
        };

        return backtrack(0);            
    }
};
