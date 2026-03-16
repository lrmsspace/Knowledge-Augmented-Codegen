// Source: https://leetcode.com/problems/where-will-the-ball-fall/   |   Difficulty: Medium
//
// Problem Description:
// You have a 2-D grid of size m x n representing a box, and you have n balls. The box is open on the top and bottom sides.
//
// Each cell in the box has a diagonal board spanning two corners of the cell that can redirect a ball to the right or to the left.
//
//
// 	A board that redirects the ball to the right spans the top-left corner to the bottom-right corner and is represented in the grid as 1.
// 	A board that redirects the ball to the left spans the top-right corner to the bottom-left corner and is represented in the grid as -1.
//
//
// We drop one ball at the top of each column of the box. Each ball can get stuck in the box or fall out of the bottom. A ball gets stuck if it hits a "V" shaped pattern between two boards or if a board redirects the ball into either wall of the box.
//
// Return an array answer of size n where answer[i] is the column that the ball falls out of at the bottom after dropping the ball from the ith column at the top, or -1 if the ball gets stuck in the box.
//
// Example:
// Input: grid = [[1,1,1,-1,-1],[1,1,1,-1,-1],[-1,-1,-1,1,1],[1,1,1,1,-1],[-1,-1,-1,-1,-1]]
// Output: [1,-1,-1,-1,-1]
// Explanation: This example is shown in the photo.
// Ball b0 is dropped at column 0 and falls out of the box at column 1.
// Ball b1 is dropped at column 1 and will get stuck in the box between column 2 and 3 and row 1.
// Ball b2 is dropped at column 2 and will get stuck on the box between column 2 and 3 and row 0.
// Ball b3 is dropped at column 3 and will get stuck on the box between column 2 and 3 and row 0.
// Ball b4 is dropped at column 4 and will get stuck on the box between column 2 and 3 and row 1.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100
// 	grid[i][j] is 1 or -1.
//
// Helpful references (internal KB):
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findBall(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * (*gridColSize));
    *returnSize = *gridColSize;

    for (int i = 0; i < *gridColSize; i++) {
        int col = i;
        for (int row = 0; row < gridSize; row++) {
            int direction = grid[row][col];
            int nextCol = col + direction;

            if (nextCol < 0 || nextCol >= *gridColSize || grid[row][nextCol] != direction) {
                col = -1;
                break;
            }
            col = nextCol;
        }
        result[i] = col;
    }

    return result;      
}
