// Source: https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums of non-negative integers, and two integers l and r.
//
// Return the count of sub-multisets within nums where the sum of elements in each subset falls within the inclusive range of [l, r].
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A sub-multiset is an unordered collection of elements of the array in which a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the number of occurrences of x in the array.
//
// Note that:
//
//
// 	Two sub-multisets are the same if sorting both sub-multisets results in identical multisets.
// 	The sum of an empty multiset is 0.
//
// Example:
// Input: nums = [1,2,2,3], l = 6, r = 6
// Output: 1
// Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	0 <= nums[i] <= 2 * 104
// 	Sum of nums does not exceed 2 * 104.
// 	0 <= l <= r <= 2 * 104
//

class Solution {
    public int countSubMultisets(List<Integer> nums, int l, int r) {
        int mod = (int)1e9 + 7;
        int maxSum = 20000;
        long[] dp = new long[maxSum + 1];
        dp[0] = 1;

        Map<Integer, Integer> freqMap = new HashMap<>();
        for (int num : nums) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        for (Map.Entry<Integer, Integer> entry : freqMap.entrySet()) {
            int num = entry.getKey();
            int count = entry.getValue();

            long[] newDp = Arrays.copyOf(dp, dp.length);
            for (int sum = 0; sum <= maxSum; sum++) {
                if (dp[sum] > 0) {
                    long ways = dp[sum];
                    for (int k = 1; k <= count; k++) {
                        int newSum = sum + k * num;
                        if (newSum > maxSum) break;
                        newDp[newSum] = (newDp[newSum] + ways) % mod;
                    }
                }
            }
            dp = newDp;
        }

        long result = 0;
        for (int sum = l; sum <= r; sum++) {
            result = (result + dp[sum]) % mod;
        }

        return (int)result;         
    }
}
