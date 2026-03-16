// Source: https://leetcode.com/problems/relative-ranks/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array score of size n, where score[i] is the score of the ith athlete in a competition. All the scores are guaranteed to be unique.
//
// The athletes are placed based on their scores, where the 1st place athlete has the highest score, the 2nd place athlete has the 2nd highest score, and so on. The placement of each athlete determines their rank:
//
//
// 	The 1st place athlete's rank is "Gold Medal".
// 	The 2nd place athlete's rank is "Silver Medal".
// 	The 3rd place athlete's rank is "Bronze Medal".
// 	For the 4th place to the nth place athlete, their rank is their placement number (i.e., the xth place athlete's rank is "x").
//
//
// Return an array answer of size n where answer[i] is the rank of the ith athlete.
//
// Example:
// Input: score = [5,4,3,2,1]
// Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
// Explanation: The placements are [1st, 2nd, 3rd, 4th, 5th].
//
// Constraints:
// n == score.length
// 	1 <= n <= 104
// 	0 <= score[i] <= 106
// 	All the values in score are unique.
//

class Solution {
    public String[] findRelativeRanks(int[] score) {
        int n = score.length;
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }

        Arrays.sort(indices, (a, b) -> Integer.compare(score[b], score[a]));

        String[] result = new String[n];
        for (int rank = 0; rank < n; rank++) {
            int athleteIndex = indices[rank];
            if (rank == 0) {
                result[athleteIndex] = "Gold Medal";
            } else if (rank == 1) {
                result[athleteIndex] = "Silver Medal";
            } else if (rank == 2) {
                result[athleteIndex] = "Bronze Medal";
            } else {
                result[athleteIndex] = String.valueOf(rank + 1);
            }
        }

        return result;          
    }
}
