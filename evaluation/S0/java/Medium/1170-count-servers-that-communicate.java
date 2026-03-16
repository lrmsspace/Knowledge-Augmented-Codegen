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

class Solution {
    public int countServers(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int[] rowCount = new int[m];
        int[] colCount = new int[n];

        // Count servers in each row and column
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }

        int communicatingServers = 0;

        // Count servers that can communicate
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && (rowCount[i] > 1 || colCount[j] > 1)) {
                    communicatingServers++;
                }
            }
        }

        return communicatingServers;            
    }
}
