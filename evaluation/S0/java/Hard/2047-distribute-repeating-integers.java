// Source: https://leetcode.com/problems/distribute-repeating-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:
//
//
// 	The ith customer gets exactly quantity[i] integers,
// 	The integers the ith customer gets are all equal, and
// 	Every customer is satisfied.
//
//
// Return true if it is possible to distribute nums according to the above conditions.
//
// Example:
// Input: nums = [1,2,3,4], quantity = [2]
// Output: false
// Explanation: The 0th customer cannot be given two different integers.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= 1000
// 	m == quantity.length
// 	1 <= m <= 10
// 	1 <= quantity[i] <= 105
// 	There are at most 50 unique values in nums.
//

class Solution {
    public boolean canDistribute(int[] nums, int[] quantity) {
        int n = quantity.length;
        int m = 1 << n;
        int[] freq = new int[1001];
        for (int num : nums) {
            freq[num]++;
        }
        List<Integer> counts = new ArrayList<>();
        for (int f : freq) {
            if (f > 0) {
                counts.add(f);
            }
        }
        boolean[] dp = new boolean[m];
        dp[0] = true;
        for (int count : counts) {
            boolean[] next = Arrays.copyOf(dp, m);
            for (int mask = 0; mask < m; mask++) {
                if (!dp[mask]) {
                    continue;
                }
                for (int submask = mask ^ (m - 1); submask > 0; submask = (submask - 1) & (mask ^ (m - 1))) {
                    int need = 0;
                    for (int i = 0; i < n; i++) {
                        if (((submask >> i) & 1) == 1) {
                            need += quantity[i];
                        }
                    }
                    if (need <= count) {
                        next[mask | submask] = true;
                    }
                }
            }
            dp = next;
        }
        return dp[m - 1];                   
    }
}
