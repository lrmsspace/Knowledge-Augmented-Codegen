// Source: https://leetcode.com/problems/number-of-provinces/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
//
// A province is a group of directly or indirectly connected cities and no other cities outside of the group.
//
// You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
//
// Return the total number of provinces.
//
// Example:
// Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
// Output: 2
//
// Constraints:
// 1 <= n <= 200
// 	n == isConnected.length
// 	n == isConnected[i].length
// 	isConnected[i][j] is 1 or 0.
// 	isConnected[i][i] == 1
// 	isConnected[i][j] == isConnected[j][i]
//

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int provinces = 0;
    int n = isConnectedSize;
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            provinces++;
            // Perform DFS to mark all connected cities
            int stack[n];
            int top = -1;
            stack[++top] = i;
            visited[i] = 1;

            while (top >= 0) {
                int city = stack[top--];
                for (int j = 0; j < n; j++) {
                    if (isConnected[city][j] == 1 && !visited[j]) {
                        visited[j] = 1;
                        stack[++top] = j;
                    }
                }
            }
        }
    }

    return provinces;       
}
