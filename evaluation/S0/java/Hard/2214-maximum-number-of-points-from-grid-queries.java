// Source: https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid and an array queries of size k.
//
// Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:
//
//
// 	If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
// 	Otherwise, you do not get any points, and you end this process.
//
//
// After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.
//
// Return the resulting array answer.
//
// Example:
// Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
// Output: [5,8,1]
// Explanation: The diagrams above show which cells we visit to get points for each query.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	k == queries.length
// 	1 <= k <= 104
// 	1 <= grid[i][j], queries[i] <= 106
//

class Solution {
    public int[] maxPoints(int[][] grid, int[] queries) {
        int m = grid.length, n = grid[0].length, size = m * n;
        int[][] cells = new int[size][3];
        for (int i = 0, idx = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells[idx++] = new int[]{grid[i][j], i, j};
            }
        }
        Arrays.sort(cells, Comparator.comparingInt(a -> a[0]));

        int qLen = queries.length;
        int[][] queriesWithIndex = new int[qLen][2];
        for (int i = 0; i < qLen; i++) {
            queriesWithIndex[i] = new int[]{queries[i], i};
        }
        Arrays.sort(queriesWithIndex, Comparator.comparingInt(a -> a[0]));

        UnionFind uf = new UnionFind(m * n);
        boolean[][] visited = new boolean[m][n];
        int[] result = new int[qLen];
        int cellIdx = 0, points = 0;
        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (int[] query : queriesWithIndex) {
            int limit = query[0], qIdx = query[1];

            while (cellIdx < size && cells[cellIdx][0] < limit) {
                int x = cells[cellIdx][1], y = cells[cellIdx][2];
                visited[x][y] = true;
                points++;

                for (int[] dir : directions) {
                    int newX = x + dir[0], newY = y + dir[1];
                    if (newX >= 0 && newX < m && newY >= 0 && newY < n && visited[newX][newY]) {
                        int root1 = uf.find(x * n + y);
                        int root2 = uf.find(newX * n + newY);
                        if (root1 != root2) {
                            uf.union(root1, root2);
                            points -= 1;
                        }
                    }
                }
                cellIdx++;
            }
            result[qIdx] = points;
        }
        return result;          
    }
}
