// Source: https://leetcode.com/problems/four-divisors/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors. If there is no such integer in the array, return 0.
//
// Example:
// Input: nums = [21,4,7]
// Output: 32
// Explanation: 
// 21 has 4 divisors: 1, 3, 7, 21
// 4 has 3 divisors: 1, 2, 4
// 7 has 2 divisors: 1, 7
// The answer is the sum of divisors of 21 only.
//
// Constraints:
// 1 <= nums.length <= 104
// 	1 <= nums[i] <= 105
//

int sumFourDivisors(int* nums, int numsSize) {
    int totalSum = 0;

    for (int i = 0; i < numsSize; i++) {
        int n = nums[i];
        int divisorCount = 0;
        int divisorSum = 0;

        for (int d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                divisorCount++;
                divisorSum += d;

                if (d * d != n) {
                    divisorCount++;
                    divisorSum += n / d;
                }

                if (divisorCount > 4) {
                    break;
                }
            }
        }

        if (divisorCount == 4) {
            totalSum += divisorSum;
        }
    }

    return totalSum;        
}
