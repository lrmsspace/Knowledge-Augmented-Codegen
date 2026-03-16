// Source: https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/   |   Difficulty: Hard
//
// Problem Description:
// In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
//
// In one move the snake can:
//
//
// 	Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
// 	
// 	Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
// 	
//
//
// Return the minimum number of moves to reach the target.
//
// If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [[0,0,0,0,0,1],
//                [1,1,0,0,1,0],
//                [0,0,0,0,1,1],
//                [0,0,1,0,1,0],
//                [0,1,1,0,0,0],
//                [0,1,1,0,0,0]]
// Output: 11
// Explanation:
// One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
//
// Constraints:
// 2 <= n <= 100
// 	0 <= grid[i][j] <= 1
// 	It is guaranteed that the snake starts at empty cells.
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
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.



int minimumMoves(int** grid, int gridSize, int* gridColSize){
    int n = gridSize;
    typedef struct {
        int r, c, dir; // dir: 0 - horizontal, 1 - vertical
    } State;
    #define MAX_STATES 20000
    State queue[MAX_STATES];
    int dist[100][100][2];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j][0] = dist[i][j][1] = -1;

    int front = 0, back = 0;
    queue[back++] = (State){0, 0, 0};
    dist[0][0][0] = 0;

    int directions[4][3] = {
        {0, 1, 0}, // right
        {1, 0, 0}, // down
        {0, 0, 1}, // rotate clockwise
        {0, 0, -1} // rotate counterclockwise
    };

    while (front < back) {
        State curr = queue[front++];
        int r = curr.r, c = curr.c, dir = curr.dir;
        if (r == n - 1 && c == n - 2 && dir == 0)
            return dist[r][c][dir];

        for (int i = 0; i < 4; ++i) {
            int nr = r + directions[i][0];
            int nc = c + directions[i][1];
            int ndir = dir + directions[i][2];

            if (ndir < 0 || ndir > 1) continue;

            if (ndir == 0) { // horizontal
                if (nr < 0 || nr >= n || nc < 0 || nc + 1 >= n) continue;
                if (grid[nr][nc] == 1 || grid[nr][nc + 1] == 1) continue;
            } else { // vertical
                if (nr < 0 || nr + 1 >= n || nc < 0 || nc >= n) continue;
                if (grid[nr][nc] == 1 || grid[nr + 1][nc] == 1) continue;
            }

            if (dist[nr][nc][ndir] == -1) {
                dist[nr][nc][ndir] = dist[r][c][dir] + 1;
                queue[back++] = (State){nr, nc, ndir};
            }
        }

}
    return -1;
}