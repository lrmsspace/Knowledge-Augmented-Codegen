// Source: https://leetcode.com/problems/snakes-and-ladders/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n integer matrix board where the cells are labeled from 1 to n2 in a Boustrophedon style starting from the bottom left of the board (i.e. board[n - 1][0]) and alternating direction each row.
//
// You start on square 1 of the board. In each move, starting from square curr, do the following:
//
//
// 	Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)].
//
// 	
// 		This choice simulates the result of a standard 6-sided die roll: i.e., there are always at most 6 destinations, regardless of the size of the board.
// 	
// 	
// 	If next has a snake or ladder, you must move to the destination of that snake or ladder. Otherwise, you move to next.
// 	The game ends when you reach the square n2.
//
//
// A board square on row r and column c has a snake or ladder if board[r][c] != -1. The destination of that snake or ladder is board[r][c]. Squares 1 and n2 are not the starting points of any snake or ladder.
//
// Note that you only take a snake or ladder at most once per dice roll. If the destination to a snake or ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.
//
//
// 	For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination square is 2. You follow the ladder to square 3, but do not follow the subsequent ladder to 4.
//
//
// Return the least number of dice rolls required to reach the square n2. If it is not possible to reach the square, return -1.
//
// Example:
// Input: board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
// Output: 4
// Explanation: 
// In the beginning, you start at square 1 (at row 5, column 0).
// You decide to move to square 2 and must take the ladder to square 15.
// You then decide to move to square 17 and must take the snake to square 13.
// You then decide to move to square 14 and must take the ladder to square 35.
// You then decide to move to square 36, ending the game.
// This is the lowest possible number of moves to reach the last square, so return 4.
//
// Constraints:
// n == board.length == board[i].length
// 	2 <= n <= 20
// 	board[i][j] is either -1 or in the range [1, n2].
// 	The squares labeled 1 and n2 are not the starting points of any snake or ladder.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int snakesAndLadders(int** board, int boardSize, int* boardColSize) {
    int n = boardSize;
    int target = n * n;
    int* dist = (int*)malloc((target + 1) * sizeof(int));
    for (int i = 1; i <= target; i++) {
        dist[i] = -1;
    }
    dist[1] = 0;

    int dir = 1; 
    int row = n - 1, col = 0; 
    int square = 1;

    int** pos = (int**)malloc((target + 1) * sizeof(int*));
    for (int i = 1; i <= target; i++) {
        pos[i] = (int*)malloc(2 * sizeof(int));
    }

    while (square <= target) {
        pos[square][0] = row;
        pos[square][1] = col;

        if (dir == 1) {
            if (col == n - 1) {
                row--;
                dir = -1;
            } else {
                col++;
            }
        } else {
            if (col == 0) {
                row--;
                dir = 1;
            } else {
                col--;
            }
        }
        square++;
    }

    int* queue = (int*)malloc((target + 1) * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = 1;

    while (front < rear) {
        int curr = queue[front++];
        for (int move = 1; move <= 6; move++) {
            int next = curr + move;
            if (next > target) break;

            int r = pos[next][0];
            int c = pos[next][1];
            if (board[r][c] != -1) {
                next = board[r][c];
            }

            if (dist[next] == -1) {
                dist[next] = dist[curr] + 1;
                queue[rear++] = next;
            }
        }
    }

    int result = dist[target];

    for (int i = 1; i <= target; i++) {
        free(pos[i]);
    }
    free(pos);
    free(dist);
    free(queue);

    return result;      
}
