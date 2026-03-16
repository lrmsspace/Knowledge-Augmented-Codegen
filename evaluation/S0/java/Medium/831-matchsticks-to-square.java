// Source: https://leetcode.com/problems/matchsticks-to-square/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
//
// Return true if you can make this square and false otherwise.
//
// Example:
// Input: matchsticks = [1,1,2,2,2]
// Output: true
// Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
//
// Constraints:
// 1 <= matchsticks.length <= 15
// 	1 <= matchsticks[i] <= 108
//

class Solution {
    public boolean makesquare(int[] matchsticks) {
        int totalLength = 0;
        for (int stick : matchsticks) {
            totalLength += stick;
        }
        if (totalLength % 4 != 0) {
            return false;
        }
        int sideLength = totalLength / 4;
        int[] sides = new int[4];
        return backtrack(matchsticks, sides, 0, sideLength);            
    }
}
