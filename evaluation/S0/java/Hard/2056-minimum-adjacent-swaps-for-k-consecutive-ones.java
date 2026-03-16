// Source: https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.
//
// Return the minimum number of moves required so that nums has k consecutive 1's.
//
// Example:
// Input: nums = [1,0,0,1,0,1], k = 2
// Output: 1
// Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is 0 or 1.
// 	1 <= k <= sum(nums)
//

class Solution {
    public int minMoves(int[] nums, int k) {
        List<Integer> ones = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == 1) {
                ones.add(i - ones.size());
            }
        }

        long[] prefix = new long[ones.size() + 1];
        for (int i = 0; i < ones.size(); i++) {
            prefix[i + 1] = prefix[i] + ones.get(i);
        }

        long result = Long.MAX_VALUE;
        for (int i = 0; i <= ones.size() - k; i++) {
            int mid = i + k / 2;
            long leftSum = prefix[mid] - prefix[i];
            long rightSum = prefix[i + k] - prefix[mid + 1];
            long median = ones.get(mid);
            long cost = rightSum - leftSum;
            if (k % 2 == 0) {
                cost -= median;
            }
            result = Math.min(result, cost);
        }

        return (int) result;            
    }
}
