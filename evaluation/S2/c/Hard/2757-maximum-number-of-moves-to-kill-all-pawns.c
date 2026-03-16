// Source: https://leetcode.com/problems/maximum-number-of-moves-to-kill-all-pawns/   |   Difficulty: Hard
//
// Problem Description:
// There is a 50 x 50 chessboard with one knight and some pawns on it. You are given two integers kx and ky where (kx, ky) denotes the position of the knight, and a 2D array positions where positions[i] = [xi, yi] denotes the position of the pawns on the chessboard.
//
// Alice and Bob play a turn-based game, where Alice goes first. In each player's turn:
//
//
// 	The player selects a pawn that still exists on the board and captures it with the knight in the fewest possible moves. Note that the player can select any pawn, it might not be one that can be captured in the least number of moves.
// 	In the process of capturing the selected pawn, the knight may pass other pawns without capturing them. Only the selected pawn can be captured in this turn.
//
//
// Alice is trying to maximize the sum of the number of moves made by both players until there are no more pawns on the board, whereas Bob tries to minimize them.
//
// Return the maximum total number of moves made during the game that Alice can achieve, assuming both players play optimally.
//
// Note that in one move, a chess knight has eight possible positions it can move to, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.
//
// Example:
// Input: kx = 1, ky = 1, positions = [[0,0]]
//
// Output: 4
//
// Explanation:
//
//
//
// The knight takes 4 moves to reach the pawn at (0, 0).
//
// Constraints:
// 0 <= kx, ky <= 49
// 	1 <= positions.length <= 15
// 	positions[i].length == 2
// 	0 <= positions[i][0], positions[i][1] <= 49
// 	All positions[i] are unique.
// 	The input is generated such that positions[i] != [kx, ky] for all 0 <= i < positions.length.
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Lowest Common Ancestor (array, sparse-table)
//   • When to use: Use this when you need to find the lowest common ancestor of many pairs of nodes in a static tree efficiently. It excels in scenarios with numerous queries after initial setup.
//   • Idea: This technique finds the LCA by transforming the problem into a Range Minimum Query (RMQ) on an Euler tour of the tree. It achieves O(N log N) precomputation time and O(1) query time.
//   • Invariants: The sparse_table[k][i] stores the minimum depth in the Euler tour array segment starting at index i and spanning 2^k elements.; The first_occurrence array correctly maps each node to its initial appearance index in the Euler tour.
//   • Tips: Perform an Euler tour (DFS traversal) to linearize the tree into an array of nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Off-by-one errors when calculating range lengths or sparse table indices.; Incorrectly handling the Euler tour array, especially when mapping back to original nodes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxMoves(int kx, int ky, int** positions, int positionsSize, int* positionsColSize) {
    // Step 1: Calculate the Manhattan distance from the knight to each pawn
    int distances[positionsSize];
    for (int i = 0; i < positionsSize; i++) {
        int px = positions[i][0];
        int py = positions[i][1];
        distances[i] = abs(kx - px) + abs(ky - py);
    }

    // Step 2: Sort the distances in descending order
    for (int i = 0; i < positionsSize - 1; i++) {
        for (int j = 0; j < positionsSize - i - 1; j++) {
            if (distances[j] < distances[j + 1]) {
                int temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
            }
        }
    }

    // Step 3: Calculate the total moves based on the sorted distances
    int totalMoves = 0;
    for (int i = 0; i < positionsSize; i++) {
        totalMoves += distances[i] + i; // Each subsequent pawn takes one more move due to previous captures
    }

    return totalMoves;
}
