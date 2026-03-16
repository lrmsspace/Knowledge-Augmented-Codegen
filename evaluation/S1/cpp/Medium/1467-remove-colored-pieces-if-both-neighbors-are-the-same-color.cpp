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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool winnerOfGame(string colors) {
        int n = colors.size();
        int aMoves = 0;
        int bMoves = 0;
        int count = 1;
        for (int i = 1; i < n; ++i) {
            if (colors[i] == colors[i - 1]) {
                ++count;
            } else {
                if (count >= 3) {
                    if (colors[i - 1] == 'A') {
                        aMoves += (count - 2);
                    } else {
                        bMoves += (count - 2);
                    }
                }
                count = 1;
            }
        }
        // Handle the last segment
        if (count >= 3) {
            if (colors[n - 1] == 'A') {
                aMoves += (count - 2);
            } else {
                bMoves += (count - 2);
            }
        }
        return aMoves > bMoves;         
    }
};
