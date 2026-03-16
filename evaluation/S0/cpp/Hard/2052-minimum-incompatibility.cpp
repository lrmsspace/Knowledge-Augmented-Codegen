// Source: https://leetcode.com/problems/minimum-incompatibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size such that there are no two equal elements in the same subset.
//
// A subset's incompatibility is the difference between the maximum and minimum elements in that array.
//
// Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.
//
// A subset is a group integers that appear in the array with no particular order.
//
// Example:
// Input: nums = [1,2,1,4], k = 2
// Output: 4
// Explanation: The optimal distribution of subsets is [1,2] and [1,4].
// The incompatibility is (2-1) + (4-1) = 4.
// Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	nums.length is divisible by k
// 	1 <= nums[i] <= nums.length
//

class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n = nums.size();
        int subsetSize = n / k;
        int totalStates = 1 << n;
        vector<int> dp(totalStates, INT_MAX);
        dp[0] = 0;

        for (int state = 0; state < totalStates; ++state) {
            if (dp[state] == INT_MAX) continue;

            vector<int> available;
            for (int i = 0; i < n; ++i) {
                if (!(state & (1 << i))) {
                    available.push_back(nums[i]);
                }
            }

            if (available.size() < subsetSize) continue;

            sort(available.begin(), available.end());

            do {
                int nextState = state;
                int minVal = available[0];
                int maxVal = available[0];
                bool valid = true;

                for (int i = 0; i < subsetSize; ++i) {
                    int idx = -1;
                    for (int j = 0; j < n; ++j) {
                        if (!(nextState & (1 << j)) && nums[j] == available[i]) {
                            idx = j;
                            break;
                        }
                    }
                    if (idx == -1) {
                        valid = false;
                        break;
                    }
                    nextState |= (1 << idx);
                    minVal = min(minVal, nums[idx]);
                    maxVal = max(maxVal, nums[idx]);
                }

                if (valid) {
                    dp[nextState] = min(dp[nextState], dp[state] + (maxVal - minVal));
                }
            } while (next_permutation(available.begin(), available.end()));
        }

        return dp[totalStates - 1] == INT_MAX ? -1 : dp[totalStates - 1];           
    }
};
