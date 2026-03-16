// Source: https://leetcode.com/problems/escape-the-spreading-fire/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three values:
//
//
// 	0 represents grass,
// 	1 represents fire,
// 	2 represents a wall that you and fire cannot pass through.
//
//
// You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, (m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all adjacent cells that are not walls.
//
// Return the maximum number of minutes that you can stay in your initial position before moving while still safely reaching the safehouse. If this is impossible, return -1. If you can always reach the safehouse regardless of the minutes stayed, return 109.
//
// Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse.
//
// A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
// Example:
// Input: grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
// Output: 3
// Explanation: The figure above shows the scenario where you stay in the initial position for 3 minutes.
// You will still be able to safely reach the safehouse.
// Staying for more than 3 minutes will not allow you to safely reach the safehouse.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 300
// 	4 <= m * n <= 2 * 104
// 	grid[i][j] is either 0, 1, or 2.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
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
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumMinutes(int** grid, int gridSize, int* gridColSize) {
     int m = gridSize, n = gridColSize[0];
    int fireTime[m][n]; // Time when fire reaches each cell
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fireTime[i][j] = -1; // Initialize fire time to -1 (unreachable)
        }
    }
    
    // Step 1: Multi-source BFS to calculate fire spread times
    int queue[m * n][2]; // Queue for BFS: [x, y]
    int front = 0, rear = 0;
    
    // Enqueue all initial fire cells
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                fireTime[i][j] = 0;
                queue[rear][0] = i;
                queue[rear][1] = j;
                rear++;
            }
        }
    }
    
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;
        
        for (int d = 0; d < 4; d++) {
            int newX = x + directions[d][0];
            int newY = y + directions[d][1];
            
            // Check bounds and walls
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] != 2 && fireTime[newX][newY] == -1) {
                fireTime[newX][newY] = fireTime[x][y] + 1;
                queue[rear][0] = newX;
                queue[rear][1] = newY;
                rear++;
            }
        }
    }
    
    // Step 2: Binary search on the number of minutes to stay at the initial position
    int left = -1, right = m * n; // Maximum possible minutes is m*n in worst
    while (left < right) {
        int mid = left + (right - left) / 2;
        // Check if we can reach the safehouse with mid minutes of waiting
        int visited[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                visited[i][j] = 0; // Initialize visited array
            }
        }
        
        // BFS to check if we can reach the safehouse
        int bfsQueue[m * n][2]; // Queue for BFS: [x, y]
        int bfsFront = 0, bfsRear = 0;
        
        if (mid < fireTime[0][0] || fireTime[0][0] == -1) { // Can we stay at the initial position for mid minutes?
            visited[0][0] = 1;
            bfsQueue[bfsRear][0] = 0;
            bfsQueue[bfsRear][1] = 0;
            bfsRear++;
        }
        
        int canReachSafehouse = 0;
        while (bfsFront < bfsRear) {
            int x = bfsQueue[bfsFront][0];
            int y = bfsQueue[bfsFront][1];
            bfsFront++;
            
            if (x == m - 1 && y == n - 1) { // Reached safehouse
                canReachSafehouse = 1;
                break;
            }
            
            for (int d = 0; d < 4; d++) {
                int newX = x + directions[d][0];
                int newY = y + directions[d][1];
                
                // Check bounds, walls, and fire timing
                if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] != 2 && !visited[newX][newY]) {
                    int arrivalTime = mid + (abs(newX - x) + abs(newY - y)); // Time when we would arrive at the new cell
                    if (arrivalTime < fireTime[newX][newY] || fireTime[newX][newY] == -1) { // Can we arrive before fire?
                        visited[newX][newY] = 1;
                        bfsQueue[bfsRear][0] = newX;
                        bfsQueue[bfsRear][1] = newY;
                        bfsRear++;
                    }
                }
            }
            
            if (canReachSafehouse) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
    }
    return left;
}