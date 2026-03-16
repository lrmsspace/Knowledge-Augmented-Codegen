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
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize){
    int n = gridSize;
    int m = gridColSize[0];
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    // Step 1: Multi-source BFS to calculate distance to nearest thief
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dist[i][j] = (grid[i][j] == 1) ? 0 : -1;
        }
    }
    
    int queueSize = n * m;
    int (*queue)[2] = malloc(queueSize * sizeof(*queue));
    int front = 0, back = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                queue[back][0] = i;
                queue[back][1] = j;
                back++;
            }
        }
    }
    
    while (front < back) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;
        
        for (int d = 0; d < 4; d++) {
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                queue[back][0] = nx;
                queue[back][1] = ny;
                back++;
            }
        }
    }
    
    free(queue);
    
    // Step 2: Binary search for maximum safeness factor
    int left = 0, right = n + m; // Maximum possible distance
    int maxSafeness = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // BFS to check if there's a path with safeness factor >= mid   
        int** visited = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) {
            visited[i] = (int*)calloc(m, sizeof(int));
        }
        int qFront = 0, qBack = 0;
        int (*q)[2] = malloc(queueSize * sizeof(*q));
        if (dist[0][0] >= mid) {
            q[qBack][0] = 0;
            q[qBack][1] = 0;
            qBack++;
            visited[0][0] = 1;
        }
        int foundPath = 0;
        while (qFront < qBack) {
            int x = q[qFront][0];
            int y = q[qFront][1];
            qFront++;
            if (x == n - 1 && y == m - 1) {
                foundPath = 1;
                break;
            }
            for (int d = 0; d < 4; d++) {
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && dist[nx][ny] >= mid) {
                    visited[nx][ny] = 1;
                    q[qBack][0] = nx;
                    q[qBack][1] = ny;
                    qBack++;
                }
            }
        }
        free(q);
        for (int i = 0; i < n; i++) {
            free(visited[i]);
        }
        free(visited);
        if (foundPath) {
            maxSafeness = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }

}
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
    return maxSafeness;
}