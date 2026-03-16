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
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public char[][] updateBoard(char[][] board, int[] click) {
        int m = board.length, n = board[0].length;
        int x = click[0], y = click[1];
        if (board[x][y] == 'M') {
            board[x][y] = 'X';
            return board;
        }
        dfs(board, x, y, m, n);
        return board;           
    }
}
