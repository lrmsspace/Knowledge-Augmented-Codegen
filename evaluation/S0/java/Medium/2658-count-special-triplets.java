// Source: https://leetcode.com/problems/count-special-triplets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// A special triplet is defined as a triplet of indices (i, j, k) such that:
//
//
// 	0 <= i < j < k < n, where n = nums.length
// 	nums[i] == nums[j] * 2
// 	nums[k] == nums[j] * 2
//
//
// Return the total number of special triplets in the array.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [6,3,6]
//
// Output: 1
//
// Explanation:
//
// The only special triplet is (i, j, k) = (0, 1, 2), where:
//
//
// 	nums[0] = 6, nums[1] = 3, nums[2] = 6
// 	nums[0] = nums[1] * 2 = 3 * 2 = 6
// 	nums[2] = nums[1] * 2 = 3 * 2 = 6
//
// Constraints:
// 3 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
//

class Solution {
    public int specialTriplets(int[] nums) {
        int MOD = 1_000_000_007;
        int maxVal = 0;
        for (int num : nums) {
            maxVal = Math.max(maxVal, num);
        }

        long[] count = new long[maxVal + 1];
        for (int num : nums) {
            count[num]++;
        }

        long result = 0;
        for (int j = 0; j <= maxVal; j++) {
            if (count[j] > 0) {
                long countJ = count[j];
                long countI = (j * 2 <= maxVal) ? count[j * 2] : 0;
                long countK = (j * 2 <= maxVal) ? count[j * 2] : 0;
                result = (result + (countI * countJ % MOD) * countK % MOD) % MOD;
            }
        }

        return (int) result;            
    }
}
