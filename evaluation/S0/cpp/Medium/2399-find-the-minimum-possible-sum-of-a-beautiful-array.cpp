// Source: https://leetcode.com/problems/find-the-minimum-possible-sum-of-a-beautiful-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given positive integers n and target.
//
// An array nums is beautiful if it meets the following conditions:
//
//
// 	nums.length == n.
// 	nums consists of pairwise distinct positive integers.
// 	There doesn't exist two distinct indices, i and j, in the range [0, n - 1], such that nums[i] + nums[j] == target.
//
//
// Return the minimum possible sum that a beautiful array could have modulo 109 + 7.
//
// Example:
// Input: n = 2, target = 3
// Output: 4
// Explanation: We can see that nums = [1,3] is beautiful.
// - The array nums has length n = 2.
// - The array nums consists of pairwise distinct positive integers.
// - There doesn't exist two distinct indices, i and j, with nums[i] + nums[j] == 3.
// It can be proven that 4 is the minimum possible sum that a beautiful array could have.
//
// Constraints:
// 1 <= n <= 109
// 	1 <= target <= 109
//

class Solution {
public:
    int minimumPossibleSum(int n, int target) {
        const int MOD = 1e9 + 7;
        long long result = 0;

        if (n <= target / 2) {
            // If n is less than or equal to half of target,
            // we can use the first n positive integers.
            result = (long long)n * (n + 1) / 2;
        } else {
            // If n is greater than half of target,
            // we can use all integers from 1 to target - 1,
            // and then add the remaining numbers starting from target + 1.
            long long halfTarget = target / 2;
            long long sumFirstPart = (long long)(target - 1) * target / 2;
            long long remainingCount = n - halfTarget;
            long long startSecondPart = target + 1;
            long long endSecondPart = target + remainingCount;
            long long sumSecondPart = (startSecondPart + endSecondPart) * remainingCount / 2;

            result = sumFirstPart + sumSecondPart;
        }

        return result % MOD;            
    }
};
