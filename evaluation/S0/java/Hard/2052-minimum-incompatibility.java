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
    public int minimumIncompatibility(int[] nums, int k) {

        int n = nums.length;
        int subsetSize = n / k;
        int fullMask = (1 << n) - 1;
        int[] dp = new int[1 << n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        for (int mask = 0; mask <= fullMask; mask++) {
            if (dp[mask] == Integer.MAX_VALUE) continue;

            List<Integer> availableIndices = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) {
                    availableIndices.add(i);
                }
            }

            if (availableIndices.size() < subsetSize) continue;

            for (int subsetMask : generateSubsets(availableIndices, subsetSize, nums)) {
                int newMask = mask | subsetMask;
                int incompatibility = calculateIncompatibility(subsetMask, nums);
                dp[newMask] = Math.min(dp[newMask], dp[mask] + incompatibility);
            }
        }

        return dp[fullMask] == Integer.MAX_VALUE ? -1 : dp[fullMask];                   
    }
}
