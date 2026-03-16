// Source: https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given a m x n matrix grid consisting of non-negative integers where grid[row][col] represents the minimum time required to be able to visit the cell (row, col), which means you can visit the cell (row, col) only when the time you visit it is greater than or equal to grid[row][col].
//
// You are standing in the top-left cell of the matrix in the 0th second, and you must move to any adjacent cell in the four directions: up, down, left, and right. Each move you make takes 1 second.
//
// Return the minimum time required in which you can visit the bottom-right cell of the matrix. If you cannot visit the bottom-right cell, then return -1.
//
// Example:
// Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
// Output: 7
// Explanation: One of the paths that we can take is the following:
// - at t = 0, we are on the cell (0,0).
// - at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
// - at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
// - at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
// - at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
// - at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
// - at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
// - at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
// The final time is 7. It can be shown that it is the minimum time possible.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	0 <= grid[i][j] <= 105
// 	grid[0][0] == 0
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//

int minimumTime(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    if (grid[0][1] > 1 && grid[1][0] > 1) return -1;

    typedef struct {
        int x, y;
        int time;
    } Node;

    #define MAX_NODES (100000 + 10)
    Node heap[MAX_NODES];
    int heapSize = 0;

    #define HEAP_SWAP(i, j) do { Node tmp = heap[i]; heap[i] = heap[j]; heap[j] = tmp; } while(0)
    #define HEAP_PUSH(node) do { \
        heap[heapSize] = node; \
        int idx = heapSize++; \
        while (idx > 0) { \
            int parent = (idx - 1) / 2; \
            if (heap[parent].time <= heap[idx].time) break; \
            HEAP_SWAP(parent, idx); \
            idx = parent; \
        } \
    } while(0)
    #define HEAP_POP() ({ \
        Node ret = heap[0]; \
        heap[0] = heap[--heapSize]; \
        int idx = 0; \
        while (1) { \
            int left = idx * 2 + 1, right = idx * 2 + 2, smallest = idx; \
            if (left < heapSize && heap[left].time < heap[smallest].time) smallest = left; \
            if (right < heapSize && heap[right].time < heap[smallest].time) smallest = right; \
            if (smallest == idx) break; \
            HEAP_SWAP(smallest, idx); \
            idx = smallest; \
        } \
        ret; \
    })

    int visited[m][n];
    memset(visited, 0, sizeof(visited));

    Node start = {0, 0, 0};
    HEAP_PUSH(start);

    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (heapSize > 0) {
        Node curr = HEAP_POP();
        int x = curr.x, y = curr.y, time = curr.time;
        if (x == m - 1 && y == n - 1) return time;      
        if (visited[x][y]) continue;
        visited[x][y] = 1;
        for (int d = 0; d < 4; d++) {
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                int arrivalTime = time + 1;
                if (arrivalTime < grid[nx][ny]) {
                    int waitTime = grid[nx][ny] - arrivalTime;
                    if (waitTime % 2 == 1) waitTime++; // wait an extra second if needed
                    arrivalTime += waitTime;
                }
                Node next = {nx, ny, arrivalTime};
                HEAP_PUSH(next);
            }
        }
    }
    return -1;
}
