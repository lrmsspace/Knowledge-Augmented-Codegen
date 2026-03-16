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
// Helpful references (internal KB):
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool winnerSquareGame(int n) {
    // Dynamic Programming approach:
    // Create a boolean array dp where dp[i] indicates whether the player whose turn it is can guarantee a win with i stones remaining.
    // Base case: dp[0] = false (if there are no stones left, the player loses).
    // For each number of stones from 1 to n, check if there is a square number of stones that can be removed (j*j <= i) such that the opponent would lose (dp[i - j*j] == false).
    // If such a move exists, set dp[i] to true, indicating the current player can guarantee a win.

    bool dp[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = false; // Initialize all states as losing
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (!dp[i - j * j]) {
                dp[i] = true; // Current player can win by removing j*j stones
                break; // No need to check further if we found a winning move
            }
        }
    }

    return dp[n]; // Return whether Alice can guarantee a win with n stones     
}
