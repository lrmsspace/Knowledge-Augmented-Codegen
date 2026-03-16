// Source: https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.
//
// Return any such subsequence as an integer array of length k.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [2,1,3,3], k = 2
// Output: [3,3]
// Explanation:
// The subsequence has the largest sum of 3 + 3 = 6.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-105 <= nums[i] <= 105
// 	1 <= k <= nums.length
//

class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end(), greater<int>());

        unordered_map<int, int> count_map;
        for (int i = 0; i < k; ++i) {
            count_map[sorted_nums[i]]++;
        }

        vector<int> result;
        for (int num : nums) {
            if (count_map[num] > 0) {
                result.push_back(num);
                count_map[num]--;
            }
        }

        return result;          
    }
};
