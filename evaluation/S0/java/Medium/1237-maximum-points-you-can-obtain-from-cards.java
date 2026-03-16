// Source: https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/   |   Difficulty: Medium
//
// Problem Description:
// There are several cards arranged in a row, and each card has an associated number of points. The points are given in the integer array cardPoints.
//
// In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
//
// Your score is the sum of the points of the cards you have taken.
//
// Given the integer array cardPoints and the integer k, return the maximum score you can obtain.
//
// Example:
// Input: cardPoints = [1,2,3,4,5,6,1], k = 3
// Output: 12
// Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
//
// Constraints:
// 1 <= cardPoints.length <= 105
// 	1 <= cardPoints[i] <= 104
// 	1 <= k <= cardPoints.length
//

class Solution {
    public int maxScore(int[] cardPoints, int k) {
        int n = cardPoints.length;
        int totalPoints = 0;

        // Calculate the total points of all cards
        for (int point : cardPoints) {
            totalPoints += point;
        }

        // If k equals the length of cardPoints, return totalPoints
        if (k == n) {
            return totalPoints;
        }

        // Find the minimum sum of the subarray of length n - k
        int windowSize = n - k;
        int currentSum = 0;

        // Calculate the sum of the first window
        for (int i = 0; i < windowSize; i++) {
            currentSum += cardPoints[i];
        }

        int minSubarraySum = currentSum;

        // Slide the window across the array
        for (int i = windowSize; i < n; i++) {
            currentSum += cardPoints[i] - cardPoints[i - windowSize];
            minSubarraySum = Math.min(minSubarraySum, currentSum);
        }

        // The maximum score is total points minus the minimum subarray sum
        return totalPoints - minSubarraySum;            
    }
}
