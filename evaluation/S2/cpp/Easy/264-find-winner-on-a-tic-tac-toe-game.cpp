// Source: https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/   |   Difficulty: Easy
//
// Problem Description:
// Tic-tac-toe is played by two players A and B on a 3 x 3 grid. The rules of Tic-Tac-Toe are:
//
//
// 	Players take turns placing characters into empty squares ' '.
// 	The first player A always places 'X' characters, while the second player B always places 'O' characters.
// 	'X' and 'O' characters are always placed into empty squares, never on filled ones.
// 	The game ends when there are three of the same (non-empty) character filling any row, column, or diagonal.
// 	The game also ends if all squares are non-empty.
// 	No more moves can be played if the game is over.
//
//
// Given a 2D integer array moves where moves[i] = [rowi, coli] indicates that the ith move will be played on grid[rowi][coli]. return the winner of the game if it exists (A or B). In case the game ends in a draw return "Draw". If there are still movements to play return "Pending".
//
// You can assume that moves is valid (i.e., it follows the rules of Tic-Tac-Toe), the grid is initially empty, and A will play first.
//
// Example:
// Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
// Output: "A"
// Explanation: A wins, they always play first.
//
// Constraints:
// 1 <= moves.length <= 9
// 	moves[i].length == 2
// 	0 <= rowi, coli <= 2
// 	There are no repeated elements on moves.
// 	moves follow the rules of tic tac toe.
//
// Helpful references (internal KB):
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
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string tictactoe(vector<vector<int>>& moves) {
        vector<vector<char>> board(3, vector<char>(3, ' '));
        char player = 'X';

        for (const auto& move : moves) {
            board[move[0]][move[1]] = player;

            // Check rows and columns
            if ((board[move[0]][0] == player && board[move[0]][1] == player && board[move[0]][2] == player) ||
                (board[0][move[1]] == player && board[1][move[1]] == player && board[2][move[1]] == player)) {
                return string(1, player);
            }

            // Check diagonals
            if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
                (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
                return string(1, player);
            }

            // Switch players
            player = (player == 'X') ? 'O' : 'X';
        }

        return (moves.size() == 9) ? "Draw" : "Pending";            
    }
};
