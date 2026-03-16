// Source: https://leetcode.com/problems/find-the-maximum-divisibility-score/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums and divisors.
//
// The divisibility score of divisors[i] is the number of indices j such that nums[j] is divisible by divisors[i].
//
// Return the integer divisors[i] with the maximum divisibility score. If multiple integers have the maximum score, return the smallest one.
//
// Example:
// Input: nums = [2,9,15,50], divisors = [5,3,7,2]
//
// Output: 2
//
// Explanation:
//
// The divisibility score of divisors[0] is 2 since nums[2] and nums[3] are divisible by 5.
//
// The divisibility score of divisors[1] is 2 since nums[1] and nums[2] are divisible by 3.
//
// The divisibility score of divisors[2] is 0 since none of the numbers in nums is divisible by 7.
//
// The divisibility score of divisors[3] is 2 since nums[0] and nums[3] are divisible by 2.
//
// As divisors[0], divisors[1], and divisors[3] have the same divisibility score, we return the smaller one which is divisors[3].
//
// Constraints:
// 1 <= nums.length, divisors.length <= 1000
// 	1 <= nums[i], divisors[i] <= 109
//

class Solution {
    public int maxDivScore(int[] nums, int[] divisors) {
        int maxScore = 0;
        int result = Integer.MAX_VALUE;

        for (int divisor : divisors) {
            int currentScore = 0;

            for (int num : nums) {
                if (num % divisor == 0) {
                    currentScore++;
                }
            }

            if (currentScore > maxScore || (currentScore == maxScore && divisor < result)) {
                maxScore = currentScore;
                result = divisor;
            }
        }

        return result;          
    }
}
