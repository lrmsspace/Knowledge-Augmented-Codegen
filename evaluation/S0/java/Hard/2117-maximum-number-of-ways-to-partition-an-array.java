// Source: https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n. The number of ways to partition nums is the number of pivot indices that satisfy both conditions:
//
//
// 	1 <= pivot < n
// 	nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]
//
//
// You are also given an integer k. You can choose to change the value of one element of nums to k, or to leave the array unchanged.
//
// Return the maximum possible number of ways to partition nums to satisfy both conditions after changing at most one element.
//
// Example:
// Input: nums = [2,-1,2], k = 3
// Output: 1
// Explanation: One optimal approach is to change nums[0] to k. The array becomes [3,-1,2].
// There is one way to partition the array:
// - For pivot = 2, we have the partition [3,-1 | 2]: 3 + -1 == 2.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	-105 <= k, nums[i] <= 105
//

class Solution {
    public int waysToPartition(int[] nums, int k) {
        int n = nums.length;
        long totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        Map<Long, Integer> leftCount = new HashMap<>();
        Map<Long, Integer> rightCount = new HashMap<>();

        long prefixSum = 0;
        for (int i = 0; i < n - 1; i++) {
            prefixSum += nums[i];
            long suffixSum = totalSum - prefixSum;
            if (prefixSum == suffixSum) {
                rightCount.put(prefixSum, rightCount.getOrDefault(prefixSum, 0) + 1);
            }
        }

        int maxWays = rightCount.getOrDefault(totalSum / 2, 0);

        prefixSum = 0;
        for (int i = 0; i < n; i++) {
            long oldNum = nums[i];
            long newNum = k;
            long diff = newNum - oldNum;

            if (i > 0) {
                prefixSum += nums[i - 1];
            }
            long suffixSum = totalSum - prefixSum - oldNum;

            if (i < n - 1) {
                if (prefixSum == suffixSum) {
                    rightCount.put(prefixSum, rightCount.get(prefixSum) - 1);
                }
            }

            long newPrefixSum = prefixSum + diff;
            long newSuffixSum = suffixSum - diff;

            int currentWays = leftCount.getOrDefault(newSuffixSum, 0) + rightCount.getOrDefault(newPrefixSum, 0);
            maxWays = Math.max(maxWays, currentWays);

            if (i < n - 1) {
                if (prefixSum == suffixSum) {
                    leftCount.put(prefixSum, leftCount.getOrDefault(prefixSum, 0) + 1);
                }
            }
        }

        return maxWays;         
    }
}
