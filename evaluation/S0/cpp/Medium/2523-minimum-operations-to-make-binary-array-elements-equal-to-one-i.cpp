// Source: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// You can do the following operation on the array any number of times (possibly zero):
//
//
// 	Choose any 3 consecutive elements from the array and flip all of them.
//
//
// Flipping an element means changing its value from 0 to 1, and from 1 to 0.
//
// Return the minimum number of operations required to make all elements in nums equal to 1. If it is impossible, return -1.
//
// Example:
// Input: nums = [0,1,1,1,0,0]
//
// Output: 3
//
// Explanation:
// We can do the following operations:
//
//
// 	Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
// 	Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
// 	Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        dp[1] = (nums[0] == 1) ? 0 : INT_MAX;
        dp[2] = (nums[0] == 1 && nums[1] == 1) ? 0 : INT_MAX;

        for (int i = 3; i <= n; ++i) {
            if (nums[i - 1] == 1) {
                dp[i] = dp[i - 1];
            }
            if (nums[i - 2] == 1 && nums[i - 1] == 1) {
                dp[i] = min(dp[i], dp[i - 2]);
            }
            if (nums[i - 3] == 0 && nums[i - 2] == 0 && nums[i - 1] == 0) {
                if (dp[i - 3] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - 3] + 1);
                }
            } else if (nums[i - 3] == 0 && nums[i - 2] == 0 && nums[i - 1] == 1) {
                if (dp[i - 3] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - 3] + 1);
                }
            } else if (nums[i - 3] == 0 && nums[i - 2] == 1 && nums[i - 1] == 0) {
                if (dp[i - 3] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - 3] + 1);
                }
            } else if (nums[i - 3] == 1 && nums[i - 2] == 0 && nums[i - 1] == 0) {
                if (dp[i - 3] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - 3] + 1);
                }
            }
        }

        return dp[n] == INT_MAX ? -1 : dp[n];           
    }
};
