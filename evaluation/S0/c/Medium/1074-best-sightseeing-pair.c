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

int maxScoreSightseeingPair(int* values, int valuesSize) {
    int max_score = 0;
    int max_i = values[0] + 0;  // This keeps track of the maximum value of (values[i] + i) seen so far.

    for (int j = 1; j < valuesSize; j++) {
        // Calculate the score for the current pair (i, j)
        int current_score = max_i + values[j] - j;
        if (current_score > max_score) {
            max_score = current_score;
        }

        // Update max_i for the next iteration
        int potential_max_i = values[j] + j;
        if (potential_max_i > max_i) {
            max_i = potential_max_i;
        }
    }

    return max_score;       
}
