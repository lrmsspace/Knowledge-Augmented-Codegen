// Source: https://leetcode.com/problems/spiral-matrix-iii/   |   Difficulty: Medium
//
// Problem Description:
// You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.
//
// You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.
//
// Return an array of coordinates representing the positions of the grid in the order you visited them.
//
// Example:
// Input: rows = 1, cols = 4, rStart = 0, cStart = 0
// Output: [[0,0],[0,1],[0,2],[0,3]]
//
// Constraints:
// 1 <= rows, cols <= 100
// 	0 <= rStart < rows
// 	0 <= cStart < cols
//
// Helpful references (internal KB):
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Minimum Enclosing Circle (array, geometry, randomized, recursion)
//   • When to use: Use when finding the smallest circle that contains a given set of 2D points. It provides an expected linear time solution for this fundamental geometric problem.
//   • Idea: Welzl's algorithm finds the unique minimum enclosing circle for a set of points using a randomized incremental approach. It achieves an expected time complexity of O(N).
//   • Invariants: The current candidate circle `C` encloses all points `p_1, ..., p_i` processed so far.; If `p_i` is not contained in `C_{i-1}`, then `p_i` must lie on the boundary of `C_i`.
//   • Tips: Randomly permute input points to ensure expected O(N) performance.; The MEC is uniquely determined by either two points forming a diameter or three points on its boundary.
//   • Pitfalls: Not randomizing the input can lead to a worst-case O(N^3) performance.; Floating-point precision issues can cause incorrect boundary checks or point containment tests.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[][] spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        int[][] result = new int[rows * cols][2];
        int[][] directions = new int[][]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // right, down, left, up

        int r = rStart;
        int c = cStart;
        int step = 1; // number of steps in the current direction
        int dirIndex = 0; // index for directions array
        int count = 0; // count of positions filled in result

        result[count++] = new int[]{r, c};

        while (count < rows * cols) {
            for (int i = 0; i < 2; i++) { // each step size is repeated twice
                for (int j = 0; j < step; j++) {
                    r += directions[dirIndex][0];
                    c += directions[dirIndex][1];

                    if (r >= 0 && r < rows && c >= 0 && c < cols) {
                        result[count++] = new int[]{r, c};
                    }
                }
                dirIndex = (dirIndex + 1) % 4; // change direction
            }
            step++; // increase step size after completing two directions
        }

        return result;          
    }
}
