// Source: https://leetcode.com/problems/maximum-score-from-removing-stones/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a solitaire game with three piles of stones of sizes a​​​​​​, b,​​​​​​ and c​​​​​​ respectively. Each turn you choose two different non-empty piles, take one stone from each, and add 1 point to your score. The game stops when there are fewer than two non-empty piles (meaning there are no more available moves).
//
// Given three integers a​​​​​, b,​​​​​ and c​​​​​, return the maximum score you can get.
//
// Example:
// Input: a = 2, b = 4, c = 6
// Output: 6
// Explanation: The starting state is (2, 4, 6). One optimal set of moves is:
// - Take from 1st and 3rd piles, state is now (1, 4, 5)
// - Take from 1st and 3rd piles, state is now (0, 4, 4)
// - Take from 2nd and 3rd piles, state is now (0, 3, 3)
// - Take from 2nd and 3rd piles, state is now (0, 2, 2)
// - Take from 2nd and 3rd piles, state is now (0, 1, 1)
// - Take from 2nd and 3rd piles, state is now (0, 0, 0)
// There are fewer than two non-empty piles, so the game ends. Total: 6 points.
//
// Constraints:
// 1 <= a, b, c <= 105
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
    public int maximumScore(int a, int b, int c) {
        int[] piles = new int[]{a, b, c};
        Arrays.sort(piles);
        int score = 0;

        while (piles[1] > 0) {
            score++;
            piles[2]--;
            piles[1]--;

            Arrays.sort(piles);
        }

        return score;           
    }
}
