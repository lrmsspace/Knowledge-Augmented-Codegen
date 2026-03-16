// Source: https://leetcode.com/problems/best-sightseeing-pair/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array values where values[i] represents the value of the ith sightseeing spot. Two sightseeing spots i and j have a distance j - i between them.
//
// The score of a pair (i < j) of sightseeing spots is values[i] + values[j] + i - j: the sum of the values of the sightseeing spots, minus the distance between them.
//
// Return the maximum score of a pair of sightseeing spots.
//
// Example:
// Input: values = [8,1,5,2,6]
// Output: 11
// Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11
//
// Constraints:
// 2 <= values.length <= 5 * 104
// 	1 <= values[i] <= 1000
//

class Solution {
    public int maxScoreSightseeingPair(int[] values) {
        int maxScore = 0;
        int maxI = values[0] + 0; // values[i] + i

        for (int j = 1; j < values.length; j++) {
            // Calculate the score for the pair (i, j)
            int currentScore = maxI + values[j] - j; // maxI is values[i] + i
            maxScore = Math.max(maxScore, currentScore);

            // Update maxI for the next iteration
            maxI = Math.max(maxI, values[j] + j);
        }

        return maxScore;            
    }
}
