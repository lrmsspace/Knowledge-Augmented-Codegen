// Source: https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbors of it if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighbors if they share one edge.
//
// Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.
//
// A binary matrix is a matrix with all cells equal to 0 or 1 only.
//
// A zero matrix is a matrix with all cells equal to 0.
//
// Example:
// Input: mat = [[0,0],[0,1]]
// Output: 3
// Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 3
// 	mat[i][j] is either 0 or 1.
//

class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int total = 1 << (m * n);
        
        vector<int> dist(total, -1);
        queue<int> q;
        
        int start = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    start |= (1 << (i * n + j));
                }
            }
        }
        
        dist[start] = 0;
        q.push(start);
        
        vector<pair<int, int>> directions = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        while (!q.empty()) {
            int state = q.front();
            q.pop();
            
            if (state == 0) {
                return dist[state];
            }
            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    int nextState = state;
                    
                    for (auto& dir : directions) {
                        int ni = i + dir.first;
                        int nj = j + dir.second;
                        
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                            nextState ^= (1 << (ni * n + nj));
                        }
                    }
                    
                    if (dist[nextState] == -1) {
                        dist[nextState] = dist[state] + 1;
                        q.push(nextState);
                    }
                }
            }
        }
        
        return -1;          
    }
};
