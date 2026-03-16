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

int minimumIncompatibility(int* nums, int numsSize, int k) {
    int n = numsSize;
    int subsetSize = n / k;
    int totalStates = 1 << n;
    int *dp = (int*)malloc(totalStates * sizeof(int));
    if (!dp) return -1;
    for (int i = 0; i < totalStates; ++i) dp[i] = -1;
    dp[0] = 0;

    for (int state = 0; state < totalStates; ++state) {
        if (dp[state] == -1) continue;

        int count = __builtin_popcount(state);
        if (count % subsetSize != 0) continue;

        for (int subset = 0; subset < totalStates; ++subset) {
            if (__builtin_popcount(subset) != subsetSize) continue;
            if ((state & subset) != 0) continue;

            int seen[17] = {0};
            int minVal = 17, maxVal = 0;
            int valid = 1;
            for (int i = 0; i < n; ++i) {
                if ((subset & (1 << i)) != 0) {
                    if (seen[nums[i]]) {
                        valid = 0;
                        break;
                    }
                    seen[nums[i]] = 1;
                    if (nums[i] < minVal) minVal = nums[i];
                    if (nums[i] > maxVal) maxVal = nums[i];
                }
            }
            if (!valid) continue;

            int newState = state | subset;
            int incompatibility = maxVal - minVal;
            if (dp[newState] == -1 || dp[newState] > dp[state] + incompatibility) {
                dp[newState] = dp[state] + incompatibility;
            }
        }
    }

    int result = dp[totalStates - 1];
    free(dp);
    return result;      
}
