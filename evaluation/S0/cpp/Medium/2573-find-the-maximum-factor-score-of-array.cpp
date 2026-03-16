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
public:
    long long maxScore(vector<int>& nums) {
        int n = nums.size();
        vector<int> gcdLeft(n), gcdRight(n);
        vector<int> lcmLeft(n), lcmRight(n);

        gcdLeft[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            gcdLeft[i] = gcd(gcdLeft[i - 1], nums[i]);
        }

        gcdRight[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            gcdRight[i] = gcd(gcdRight[i + 1], nums[i]);
        }

        lcmLeft[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            lcmLeft[i] = lcm(lcmLeft[i - 1], nums[i]);
        }

        lcmRight[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            lcmRight[i] = lcm(lcmRight[i + 1], nums[i]);
        }

        long long maxScore = 0;
        for (int i = 0; i < n; ++i) {
            int currGCD = (i == 0) ? gcdRight[1] : (i == n - 1) ? gcdLeft[n - 2] : gcd(gcdLeft[i - 1], gcdRight[i + 1]);
            int currLCM = (i == 0) ? lcmRight[1] : (i == n - 1) ? lcmLeft[n - 2] : lcm(lcmLeft[i - 1], lcmRight[i + 1]);
            maxScore = max(maxScore, (long long)currGCD * currLCM);
        }

        return maxScore;            
    }
};
