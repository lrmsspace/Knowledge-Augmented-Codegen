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

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize){
    int n = gridSize;
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    int dist[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dist[i][j] = 1e9;
    
    // Multi-source BFS to calculate distance from nearest thief
    int queue[n*n][2];
    int front = 0, rear = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j] == 1){
                dist[i][j] = 0;
                queue[rear][0] = i;
                queue[rear][1] = j;
                rear++;
            }
        }
    }
    
    while(front < rear){
        int x = queue[front][0];
        int y = queue[front][1];
        front++;
        
        for(int d=0;d<4;d++){
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];
            if(nx >= 0 && nx < n && ny >= 0 && ny < n){
                if(dist[nx][ny] > dist[x][y] + 1){
                    dist[nx][ny] = dist[x][y] + 1;
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    rear++;
                }
            }
        }
    }
    
    // Binary search for maximum safeness factor
    int left = 0, right = n*2, ans = 0;
    while(left <= right){
        int mid = (left + right) / 2;
        
        // BFS to check if there's a path with safeness factor >= mid
        int visited[n][n];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                visited[i][j] = 0;
        
        if(dist[0][0] < mid){
            right = mid - 1;
            continue;
        }
        
        front = 0; rear = 0;
        queue[rear][0] = 0;
        queue[rear][1] = 0;
        rear++;
        visited[0][0] = 1;
        
        int found = 0;
        while(front < rear){
            int x = queue[front][0];
            int y = queue[front][1];
            front++;
            
            if(x == n-1 && y == n-1){
                found = 1;
                break;
            }
            
            for(int d=0;d<4;d++){
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];
                if(nx >= 0 && nx < n && ny >= 0 && ny < n){
                    if(!visited[nx][ny] && dist[nx][ny] >= mid){
                        visited[nx][ny] = 1;
                        queue[rear][0] = nx;
                        queue[rear][1] = ny;
                        rear++;
                    }
                }
            }
        }
        
        if(found){
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return ans;
}