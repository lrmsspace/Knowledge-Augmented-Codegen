// Source: https://leetcode.com/problems/last-day-where-you-can-still-cross/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given integers row and col representing the number of rows and columns in the matrix, respectively.
//
// Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row and cith column (1-based coordinates) will be covered with water (i.e., changed to 1).
//
// You want to find the last day that it is possible to walk from the top to the bottom by only walking on land cells. You can start from any cell in the top row and end at any cell in the bottom row. You can only travel in the four cardinal directions (left, right, up, and down).
//
// Return the last day where it is possible to walk from the top to the bottom by only walking on land cells.
//
// Example:
// Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
// Output: 2
// Explanation: The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 2.
//
// Constraints:
// 2 <= row, col <= 2 * 104
// 	4 <= row * col <= 2 * 104
// 	cells.length == row * col
// 	1 <= ri <= row
// 	1 <= ci <= col
// 	All the values of cells are unique.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int latestDayToCross(int row, int col, int** cells, int cellsSize, int* cellsColSize) {
    int left = 1, right = cellsSize;
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (left < right) {
        int mid = left + (right - left + 1) / 2;

        /* Create grid and mark flooded cells */
        char *grid = (char*)calloc(row * col, sizeof(char));
        for (int i = 0; i < mid; i++) {
            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;
            grid[r * col + c] = 1; /* flooded */
        }

        /* Multi-source BFS from top row */
        char *visited = (char*)calloc(row * col, sizeof(char));
        int *queue = (int*)malloc(row * col * sizeof(int));
        int front = 0, back = 0;

        for (int c = 0; c < col; c++) {
            if (grid[c] == 0) { /* land */
                queue[back++] = c;
                visited[c] = 1;
            }
        }

        int canCross = 0;
        while (front < back) {
            int pos = queue[front++];
            int r = pos / col;
            int c = pos % col;

            if (r == row - 1) {
                canCross = 1;
                break;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + directions[d][0];
                int nc = c + directions[d][1];
                if (nr >= 0 && nr < row && nc >= 0 && nc < col) {
                    int npos = nr * col + nc;
                    if (grid[npos] == 0 && !visited[npos]) {
                        visited[npos] = 1;
                        queue[back++] = npos;
                    }
                }
            }
        }

        free(grid);
        free(visited);
        free(queue);

        if (canCross) {
            left = mid; /* try later day */
        } else {
            right = mid - 1; /* try earlier day */
        }
    }

    return left;        
}
