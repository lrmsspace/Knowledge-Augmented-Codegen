// Source: https://leetcode.com/problems/stone-game-iv/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob take turns playing a game, with Alice starting first.
//
// Initially, there are n stones in a pile. On each player's turn, that player makes a move consisting of removing any non-zero square number of stones in the pile.
//
// Also, if a player cannot make a move, he/she loses the game.
//
// Given a positive integer n, return true if and only if Alice wins the game otherwise return false, assuming both players play optimally.
//
// Example:
// Input: n = 1
// Output: true
// Explanation: Alice can remove 1 stone winning the game because Bob doesn't have any moves.
//
// Constraints:
// 1 <= n <= 105
//

bool winnerSquareGame(int n) {
    bool *dp = (bool*)calloc(n + 1, sizeof(bool));
    if (!dp) return false; /* allocation failure */
    for (int i = 1; i <= n; i++) {
        for (int sq = 1; sq * sq <= i; sq++) {
            if (!dp[i - sq * sq]) {
                dp[i] = true;
                break;
            }
        }
    }
    bool result = dp[n];
    free(dp);
    return result;      
}
