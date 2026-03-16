// Source: https://leetcode.com/problems/trapping-rain-water-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
//
// Example:
// Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
// Explanation: After the rain, water is trapped between the blocks.
// We have two small ponds 1 and 3 units trapped.
// The total volume of water trapped is 4.
//
// Constraints:
// m == heightMap.length
// 	n == heightMap[i].length
// 	1 <= m, n <= 200
// 	0 <= heightMap[i][j] <= 2 * 104
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// Helper structure for priority queue (min-heap)
typedef struct {
    int row;
    int col;
    int height;
} Cell;

// Helper function to swap two cells
void swap(Cell* a, Cell* b) {
    Cell temp = *a;
    *a = *b;
    *b = temp;
}

// Min-heap operations
void heapifyUp(Cell* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[idx].height < heap[parent].height) {
            swap(&heap[idx], &heap[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(Cell* heap, int size, int idx) {
    while (idx * 2 + 1 < size) {
        int left = idx * 2 + 1;
        int right = idx * 2 + 2;
        int smallest = idx;
        
        if (left < size && heap[left].height < heap[smallest].height) {
            smallest = left;
        }
        if (right < size && heap[right].height < heap[smallest].height) {
            smallest = right;
        }
        
        if (smallest != idx) {
            swap(&heap[idx], &heap[smallest]);
            idx = smallest;
        } else {
            break;
        }
    }
}

void heapPush(Cell* heap, int* size, Cell cell) {
    heap[*size] = cell;
    heapifyUp(heap, *size);
    (*size)++;
}

Cell heapPop(Cell* heap, int* size) {
    Cell result = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapifyDown(heap, *size, 0);
    return result;
}

int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize) {
    if (heightMapSize == 0 || heightMapColSize[0] == 0) {
        return 0;
    }
    
    int m = heightMapSize;
    int n = heightMapColSize[0];
    
    // Allocate visited array
    int** visited = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        visited[i] = (int*)calloc(n, sizeof(int));
    }
    
    // Priority queue (min-heap)
    Cell* heap = (Cell*)malloc(m * n * sizeof(Cell));
    int heapSize = 0;
    
    // Add all border cells to the heap and mark as visited
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                Cell cell = {i, j, heightMap[i][j]};
                heapPush(heap, &heapSize, cell);
                visited[i][j] = 1;
            }
        }
    }
    
    int waterTrapped = 0;
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // Process cells from lowest to highest
    while (heapSize > 0) {
        Cell current = heapPop(heap, &heapSize);
        
        // Check all 4 neighbors
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dirs[i][0];
            int newCol = current.col + dirs[i][1];
            
            // Check bounds and visited status
            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && !visited[newRow][newCol]) {
                visited[newRow][newCol] = 1;
                
                // Calculate water that can be trapped at this cell
                int cellHeight = heightMap[newRow][newCol];
                if (cellHeight < current.height) {
                    waterTrapped += current.height - cellHeight;
                }
                
                // Add neighbor to heap with the maximum of its height and current water level
                Cell neighbor = {newRow, newCol, cellHeight > current.height ? cellHeight : current.height};
                heapPush(heap, &heapSize, neighbor);
            }
        }
    }
    
    // Free allocated memory
    for (int i = 0; i < m; i++) {
        free(visited[i]);
    }
    free(visited);
    free(heap);
    
    return waterTrapped;
}