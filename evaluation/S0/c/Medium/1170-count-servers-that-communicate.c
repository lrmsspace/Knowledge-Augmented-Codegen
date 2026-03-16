// Source: https://leetcode.com/problems/count-servers-that-communicate/   |   Difficulty: Medium
//
// Problem Description:
// You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server. Two servers are said to communicate if they are on the same row or on the same column.
//
// Return the number of servers that communicate with any other server.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 0
// Explanation: No servers can communicate with others.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m <= 250
// 	1 <= n <= 250
// 	grid[i][j] == 0 or 1
//

int countServers(int** grid, int gridSize, int* gridColSize) {
    int rowCount[250] = {0};
    int colCount[250] = {0};
    int result = 0;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1) {
                rowCount[i]++;
                colCount[j]++;
            }
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1 && (rowCount[i] > 1 || colCount[j] > 1)) {
                result++;
            }
        }
    }

    return result;      
}
