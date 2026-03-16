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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean makesquare(int[] matchsticks) {
        int sum = 0;
        for (int stick : matchsticks) {
            sum += stick;
        }
        if (sum % 4 != 0) {
            return false;
        }
        int sideLength = sum / 4;
        Arrays.sort(matchsticks);
        return backtrack(matchsticks, new int[4], matchsticks.length - 1, sideLength);          
    }
}
