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
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* tictactoe(int** moves, int movesSize, int* movesColSize) {
    int board[3][3] = {0};
    for (int i = 0; i < movesSize; ++i) {
        int r = moves[i][0];
        int c = moves[i][1];
        board[r][c] = (i % 2 == 0) ? 1 : -1;  // A: 1, B: -1
    }

    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        int rowSum = board[i][0] + board[i][1] + board[i][2];
        int colSum = board[0][i] + board[1][i] + board[2][i];
        if (rowSum == 3 || colSum == 3) return "A";
        if (rowSum == -3 || colSum == -3) return "B";
    }

    // Check diagonals
    int diag1Sum = board[0][0] + board[1][1] + board[2][2];
    int diag2Sum = board[0][2] + board[1][1] + board[2][0];
    if (diag1Sum == 3 || diag2Sum == 3) return "A";
    if (diag1Sum == -3 || diag2Sum == -3) return "B";

    // Check for draw or pending
    return (movesSize == 9) ? "Draw" : "Pending";       
}
