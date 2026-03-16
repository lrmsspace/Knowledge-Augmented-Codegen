// Source: https://leetcode.com/problems/maximize-subarray-gcd-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and an integer k.
//
// You may perform at most k operations. In each operation, you can choose one element in the array and double its value. Each element can be doubled at most once.
//
// The score of a contiguous subarray is defined as the product of its length and the greatest common divisor (GCD) of all its elements.
//
// Your task is to return the maximum score that can be achieved by selecting a contiguous subarray from the modified array.
//
// Note:
//
//
//  The greatest common divisor (GCD) of an array is the largest integer that evenly divides all the array elements.
//
// Example:
// Input: nums = [2,4], k = 1
//
// Output: 8
//
// Explanation:
//
//
//  Double nums[0] to 4 using one operation. The modified array becomes [4, 4].
//  The GCD of the subarray [4, 4] is 4, and the length is 2.
//  Thus, the maximum possible score is 2 × 4 = 8.
//
// Constraints:
// 1 <= n == nums.length <= 1500
//  1 <= nums[i] <= 109
//  1 <= k <= n
//

class Solution {
    public long maxGCDScore(int[] nums, int k) {
        int n = nums.length;
        long maxScore = 0;

        for (int i = 0; i < n; i++) {
            int gcdCandidate = nums[i];
            int operationsUsed = 0;
            long currentScore = 0;

            for (int j = i; j < n; j++) {
                int currentNum = nums[j];
                int newGCD = gcd(gcdCandidate, currentNum);

                if (newGCD < gcdCandidate) {
                    int requiredDoublings = (gcdCandidate % 2 == 0 && currentNum * 2 >= gcdCandidate) ? 1 : 0;

                    if (requiredDoublings + operationsUsed <= k) {
                        operationsUsed += requiredDoublings;
                        currentNum *= (requiredDoublings == 1) ? 2 : 1;
                        newGCD = gcd(gcdCandidate, currentNum);
                    } else {
                        break;
                    }
                }

                gcdCandidate = newGCD;
                currentScore = (long) (j - i + 1) * gcdCandidate;
                maxScore = Math.max(maxScore, currentScore);
            }
        }

        return maxScore;            
    }
}
