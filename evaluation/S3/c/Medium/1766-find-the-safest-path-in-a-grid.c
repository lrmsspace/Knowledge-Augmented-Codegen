// Source: https://leetcode.com/problems/find-the-safest-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:
//
//
// 	A cell containing a thief if grid[r][c] = 1
// 	An empty cell if grid[r][c] = 0
//
//
// You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.
//
// The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.
//
// Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).
//
// An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.
//
// The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.
//
// Example:
// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
// Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
//
// Constraints:
// 1 <= grid.length == n <= 400
// 	grid[i].length == n
// 	grid[i][j] is either 0 or 1.
// 	There is at least one thief in the grid.
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Hungarian algorithm for solving the assignment problem (matrix, graph, greedy, bfs)
//   • When to use: Finds shortest paths in unweighted graphs or uniform-cost state-space searches. Explores states layer by layer.
//   • Idea: Explores all reachable nodes in a graph layer by layer, finding the shortest path in unweighted graphs. It operates in O(V + E) time complexity.
//   • Invariants: All nodes currently in the queue are at the same distance from the source.; All nodes visited so far have their shortest distance from the source determined.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops.; Incorrectly handling disconnected components.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize){
    // Step 1: Multi-source BFS to calculate the minimum distance from each cell to the nearest thief
    int n = gridSize;
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1; // Initialize distances to -1
        }
    }

    // Queue for BFS
    typedef struct {
        int x, y;
    } Point;

    Point* queue = (Point*)malloc(n * n * sizeof(Point));
    int front = 0, rear = 0;

    // Enqueue all thieves and set their distance to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                queue[rear++] = (Point){i, j};
                dist[i][j] = 0;
            }
        }
    }

    // Directions for moving up, down, left, right
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (front < rear) {
        Point current = queue[front++];
        int currentDist = dist[current.x][current.y];

        for (int d = 0; d < 4; d++) {
            int newX = current.x + directions[d][0];
            int newY = current.y + directions[d][1];

            if (newX >= 0 && newX < n && newY >= 0 && newY < n && dist[newX][newY] == -1) {
                dist[newX][newY] = currentDist + 1;
                queue[rear++] = (Point){newX, newY};
            }
        }
    }

    // Step 2: Binary search on the safeness factor and check if there's a valid path
    int left = 0, right = n * 2; // Maximum possible distance in the grid

    while (left < right) {
        int mid = left + (right - left) / 2;
        // Check if there's a path from (0, 0) to (n - 1, n - 1) with safeness factor >= mid
        if (dist[0][0] >= mid && dist[n - 1][n - 1] >= mid) {
            // BFS to check if we can reach the destination with the given safeness factor
            int visited[400][400] = {0}; // Assuming n <= 400
            Point bfsQueue[160000]; // Queue for BFS
            int bfsFront = 0, bfsRear = 0;

            bfsQueue[bfsRear++] = (Point){0, 0};
            visited[0][0] = 1;
            int foundPath = 0;

            while (bfsFront < bfsRear) {
                Point current = bfsQueue[bfsFront++];
                if (current.x == n - 1 && current.y == n - 1) {
                    foundPath = 1;
                    break;
                }

                for (int d = 0; d < 4; d++) {
                    int newX = current.x + directions[d][0];
                    int newY = current.y + directions[d][1];

                    if (newX >= 0 && newX < n && newY >= 0 && newY < n &&
                        !visited[newX][newY] && dist[newX][newY] >= mid) {
                        visited[newX][newY] = 1;
                        bfsQueue[bfsRear++] = (Point){newX, newY};
                    }
                }
            }

            if (foundPath) {
                left = mid + 1; // Try for a higher safeness factor
            } else {
                right = mid; // Try for a lower safeness factor
            }
        } else {
            right = mid; // If starting or ending cell is not safe enough, try lower safeness factor
        }
    }
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
    free(queue);
    return left - 1; // The maximum safeness factor is left - 1 after the loop
}
