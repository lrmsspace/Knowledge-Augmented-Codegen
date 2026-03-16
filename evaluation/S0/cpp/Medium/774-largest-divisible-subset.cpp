// Source: https://leetcode.com/problems/largest-divisible-subset/   |   Difficulty: Medium
//
// Problem Description:
// Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
//
//
// 	answer[i] % answer[j] == 0, or
// 	answer[j] % answer[i] == 0
//
//
// If there are multiple solutions, return any of them.
//
// Example:
// Input: nums = [1,2,3]
// Output: [1,2]
// Explanation: [1,3] is also accepted.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 2 * 109
// 	All the integers in nums are unique.
//

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> dp(n, 1), prev(n, -1);
        int maxSize = 1, maxIndex = 0;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
            if (dp[i] > maxSize) {
                maxSize = dp[i];
                maxIndex = i;
            }
        }

        vector<int> result;
        while (maxIndex != -1) {
            result.push_back(nums[maxIndex]);
            maxIndex = prev[maxIndex];
        }
        reverse(result.begin(), result.end());
        return result;          
    }
};
