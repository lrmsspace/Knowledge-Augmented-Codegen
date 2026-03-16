// Source: https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are currently designing a dynamic array. You are given a 0-indexed integer array nums, where nums[i] is the number of elements that will be in the array at time i. In addition, you are given an integer k, the maximum number of times you can resize the array (to any size).
//
// The size of the array at time t, sizet, must be at least nums[t] because there needs to be enough space in the array to hold all the elements. The space wasted at time t is defined as sizet - nums[t], and the total space wasted is the sum of the space wasted across every time t where 0 <= t < nums.length.
//
// Return the minimum total space wasted if you can resize the array at most k times.
//
// Note: The array can have any size at the start and does not count towards the number of resizing operations.
//
// Example:
// Input: nums = [10,20], k = 0
// Output: 10
// Explanation: size = [20,20].
// We can set the initial size to be 20.
// The total wasted space is (20 - 10) + (20 - 20) = 10.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 106
// 	0 <= k <= nums.length - 1
//

class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 2, INT_MAX));
        vector<vector<int>> waste(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            int maxNum = nums[i];
            for (int j = i; j < n; ++j) {
                maxNum = max(maxNum, nums[j]);
                waste[i][j] = (j - i + 1) * maxNum - accumulate(nums.begin() + i, nums.begin() + j + 1, 0);
            }
        }

        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                for (int p = 0; p < i; ++p) {
                    if (dp[p][j] != INT_MAX) {
                        dp[i][j + 1] = min(dp[i][j + 1], dp[p][j] + waste[p][i - 1]);
                    }
                }
            }
        }

        return *min_element(dp[n].begin(), dp[n].end());            
    }
};
