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
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int maxScore = 0;
        int bestI = values[0] + 0; // values[i] + i

        for (int j = 1; j < values.size(); ++j) {
            int currentScore = bestI + values[j] - j; // values[i] + values[j] + i - j
            maxScore = max(maxScore, currentScore);
            bestI = max(bestI, values[j] + j); // Update bestI for next iteration
        }

        return maxScore;            
    }
};
