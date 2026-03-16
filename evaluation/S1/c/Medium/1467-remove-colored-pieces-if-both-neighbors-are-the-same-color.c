// Source: https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/   |   Difficulty: Medium
//
// Problem Description:
// There are n pieces arranged in a line, and each piece is colored either by 'A' or by 'B'. You are given a string colors of length n where colors[i] is the color of the ith piece.
//
// Alice and Bob are playing a game where they take alternating turns removing pieces from the line. In this game, Alice moves first.
//
//
// 	Alice is only allowed to remove a piece colored 'A' if both its neighbors are also colored 'A'. She is not allowed to remove pieces that are colored 'B'.
// 	Bob is only allowed to remove a piece colored 'B' if both its neighbors are also colored 'B'. He is not allowed to remove pieces that are colored 'A'.
// 	Alice and Bob cannot remove pieces from the edge of the line.
// 	If a player cannot make a move on their turn, that player loses and the other player wins.
//
//
// Assuming Alice and Bob play optimally, return true if Alice wins, or return false if Bob wins.
//
// Example:
// Input: colors = "AAABABB"
// Output: true
// Explanation:
// AAABABB -> AABABB
// Alice moves first.
// She removes the second 'A' from the left since that is the only 'A' whose neighbors are both 'A'.
//
// Now it's Bob's turn.
// Bob cannot make a move on his turn since there are no 'B's whose neighbors are both 'B'.
// Thus, Alice wins, so return true.
//
// Constraints:
// 1 <= colors.length <= 105
// 	colors consists of only the letters 'A' and 'B'
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool winnerOfGame(char* colors) {
    int countA = 0, countB = 0;
    int len = 0;
    char prevChar = '\0';

    for (int i = 0; colors[i] != '\0'; i++) {
        if (colors[i] == prevChar) {
            len++;
        } else {
            if (len >= 3) {
                if (prevChar == 'A') {
                    countA += (len - 2);
                } else if (prevChar == 'B') {
                    countB += (len - 2);
                }
            }
            len = 1;
            prevChar = colors[i];
        }
    }

    // Handle the last sequence
    if (len >= 3) {
        if (prevChar == 'A') {
            countA += (len - 2);
        } else if (prevChar == 'B') {
            countB += (len - 2);
        }
    }

    return countA > countB;     
}
