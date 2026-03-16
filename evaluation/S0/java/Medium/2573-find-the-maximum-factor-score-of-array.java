// Source: https://leetcode.com/problems/find-the-maximum-factor-score-of-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// The factor score of an array is defined as the product of the LCM and GCD of all elements of that array.
//
// Return the maximum factor score of nums after removing at most one element from it.
//
// Note that both the LCM and GCD of a single number are the number itself, and the factor score of an empty array is 0.
//
// Example:
// Input: nums = [2,4,8,16]
//
// Output: 64
//
// Explanation:
//
// On removing 2, the GCD of the rest of the elements is 4 while the LCM is 16, which gives a maximum factor score of 4 * 16 = 64.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 30
//

class Solution {
    public long maxScore(int[] nums) {
        int n = nums.length;

        int[] prefixGCD = new int[n];
        int[] suffixGCD = new int[n];
        int[] prefixLCM = new int[n];
        int[] suffixLCM = new int[n];

        prefixGCD[0] = nums[0];
        prefixLCM[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixGCD[i] = gcd(prefixGCD[i - 1], nums[i]);
            prefixLCM[i] = lcm(prefixLCM[i - 1], nums[i]);
        }

        suffixGCD[n - 1] = nums[n - 1];
        suffixLCM[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixGCD[i] = gcd(suffixGCD[i + 1], nums[i]);
            suffixLCM[i] = lcm(suffixLCM[i + 1], nums[i]);
        }

        long maxScore = prefixGCD[n - 1] * prefixLCM[n - 1];

        for (int i = 0; i < n; i++) {
            int currentGCD = (i == 0) ? suffixGCD[1] : (i == n - 1) ? prefixGCD[n - 2] : gcd(prefixGCD[i - 1], suffixGCD[i + 1]);
            int currentLCM = (i == 0) ? suffixLCM[1] : (i == n - 1) ? prefixLCM[n - 2] : lcm(prefixLCM[i - 1], suffixLCM[i + 1]);

            maxScore = Math.max(maxScore, (long) currentGCD * currentLCM);
        }

        return maxScore;            
    }
}
