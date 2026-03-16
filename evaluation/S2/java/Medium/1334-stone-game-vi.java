// Source: https://leetcode.com/problems/stone-game-vi/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob take turns playing a game, with Alice starting first.
//
// There are n stones in a pile. On each player's turn, they can remove a stone from the pile and receive points based on the stone's value. Alice and Bob may value the stones differently.
//
// You are given two integer arrays of length n, aliceValues and bobValues. Each aliceValues[i] and bobValues[i] represents how Alice and Bob, respectively, value the ith stone.
//
// The winner is the person with the most points after all the stones are chosen. If both players have the same amount of points, the game results in a draw. Both players will play optimally. Both players know the other's values.
//
// Determine the result of the game, and:
//
//
// 	If Alice wins, return 1.
// 	If Bob wins, return -1.
// 	If the game results in a draw, return 0.
//
// Example:
// Input: aliceValues = [1,3], bobValues = [2,1]
// Output: 1
// Explanation:
// If Alice takes stone 1 (0-indexed) first, Alice will receive 3 points.
// Bob can only choose stone 0, and will only receive 2 points.
// Alice wins.
//
// Constraints:
// n == aliceValues.length == bobValues.length
// 	1 <= n <= 105
// 	1 <= aliceValues[i], bobValues[i] <= 100
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
    public int stoneGameVI(int[] aliceValues, int[] bobValues) {
        int n = aliceValues.length;
        int[][] stones = new int[n][3];
        for (int i = 0; i < n; i++) {
            stones[i][0] = aliceValues[i] + bobValues[i]; // total value of the stone
            stones[i][1] = aliceValues[i]; // Alice's value
            stones[i][2] = bobValues[i]; // Bob's value
        }

        // Sort the stones based on total value in descending order
        Arrays.sort(stones, (a, b) -> Integer.compare(b[0], a[0]));

        int aliceScore = 0;
        int bobScore = 0;

        // Players take turns picking the stone with the highest total value
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) { // Alice's turn
                aliceScore += stones[i][1];
            } else { // Bob's turn
                bobScore += stones[i][2];
            }
        }

        if (aliceScore > bobScore) {
            return 1; // Alice wins
        } else if (bobScore > aliceScore) {
            return -1; // Bob wins
        } else {
            return 0; // Draw
        }           
    }
}
