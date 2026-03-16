// Source: https://leetcode.com/problems/minesweeper/   |   Difficulty: Medium
//
// Problem Description:
// Let's play the minesweeper game (Wikipedia, online game)!
//
// You are given an m x n char matrix board representing the game board where:
//
//
// 	'M' represents an unrevealed mine,
// 	'E' represents an unrevealed empty square,
// 	'B' represents a revealed blank square that has no adjacent mines (i.e., above, below, left, right, and all 4 diagonals),
// 	digit ('1' to '8') represents how many mines are adjacent to this revealed square, and
// 	'X' represents a revealed mine.
//
//
// You are also given an integer array click where click = [clickr, clickc] represents the next click position among all the unrevealed squares ('M' or 'E').
//
// Return the board after revealing this position according to the following rules:
//
//
// 	If a mine 'M' is revealed, then the game is over. You should change it to 'X'.
// 	If an empty square 'E' with no adjacent mines is revealed, then change it to a revealed blank 'B' and all of its adjacent unrevealed squares should be revealed recursively.
// 	If an empty square 'E' with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
// 	Return the board when no more squares will be revealed.
//
// Example:
// Input: board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
// Output: [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 50
// 	board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
// 	click.length == 2
// 	0 <= clickr < m
// 	0 <= clickc < n
// 	board[clickr][clickc] is either 'M' or 'E'.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Gauss method for solving system of linea (bitset, matrix, simulation)
//   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
//   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
//   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
//   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
//   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private final int[][] directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    private void dfs(char[][] board, int row, int col, int rows, int cols) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != 'E') {
            return;
        }

        int mineCount = 0;
        for (int[] dir : directions) {
            int newRow = row + dir[0];
            int newCol = col + dir[1];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && board[newRow][newCol] == 'M') {
                mineCount++;
            }
        }

        if (mineCount > 0) {
            board[row][col] = (char) (mineCount + '0');
        } else {
            board[row][col] = 'B';
            for (int[] dir : directions) {
                dfs(board, row + dir[0], col + dir[1], rows, cols);
            }
        }
    }
    public char[][] updateBoard(char[][] board, int[] click) {
        int rows = board.length;
        int cols = board[0].length;
        int clickRow = click[0];
        int clickCol = click[1];

        if (board[clickRow][clickCol] == 'M') {
            board[clickRow][clickCol] = 'X';
        } else {
            dfs(board, clickRow, clickCol, rows, cols);
        }

        return board;           
    }
}
