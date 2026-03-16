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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** updateBoard(char** board, int boardSize, int* boardColSize, int* click, int clickSize, int* returnSize, int** returnColumnSizes) {
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0}, {1, 1}
    };
    
    int rows = boardSize;
    int cols = boardColSize[0];
    int clickRow = click[0];
    int clickCol = click[1];
    
    if (board[clickRow][clickCol] == 'M') {
        board[clickRow][clickCol] = 'X';
        *returnSize = boardSize;
        *returnColumnSizes = boardColSize;
        return board;
    }
    
    // BFS initialization
    int queueSize = rows * cols;
    int (*queue)[2] = malloc(queueSize * sizeof(*queue));
    int front = 0, back = 0;
    
    queue[back][0] = clickRow;
    queue[back][1] = clickCol;
    back++;
    
    while (front < back) {
        int r = queue[front][0];
        int c = queue[front][1];
        front++;
        
        if (board[r][c] != 'E') {
            continue;
        }
        
        // Count adjacent mines
        int mineCount = 0;
        for (int i = 0; i < 8; i++) {
            int newRow = r + directions[i][0];
            int newCol = c + directions[i][1];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                if (board[newRow][newCol] == 'M') {
                    mineCount++;
                }
            }
        }
        
        if (mineCount > 0) {
            board[r][c] = '0' + mineCount;
        } else {
            board[r][c] = 'B';
            for (int i = 0; i < 8; i++) {
                int newRow = r + directions[i][0];
                int newCol = c + directions[i][1];
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                    if (board[newRow][newCol] == 'E') {
                        queue[back][0] = newRow;
                        queue[back][1] = newCol;
                        back++;
                    }
                }
            }
        }
    }
    free(queue);
    *returnSize = boardSize;
    *returnColumnSizes = boardColSize;
    return board;   
}
