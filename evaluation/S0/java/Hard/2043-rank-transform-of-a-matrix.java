// Source: https://leetcode.com/problems/rank-transform-of-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].
//
// The rank is an integer that represents how large an element is compared to other elements. It is calculated using the following rules:
//
//
// 	The rank is an integer starting from 1.
// 	If two elements p and q are in the same row or column, then:
// 	
// 		If p < q then rank(p) < rank(q)
// 		If p == q then rank(p) == rank(q)
// 		If p > q then rank(p) > rank(q)
// 	
// 	
// 	The rank should be as small as possible.
//
//
// The test cases are generated so that answer is unique under the given rules.
//
// Example:
// Input: matrix = [[1,2],[3,4]]
// Output: [[1,2],[2,3]]
// Explanation:
// The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
// The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][0] is rank 1.
// The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1.
// The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and both matrix[0][1] and matrix[1][0] are rank 2.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 500
// 	-109 <= matrix[row][col] <= 109
//

class Solution {
    public int[][] matrixRankTransform(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length;
        int[] rowMax = new int[m];
        int[] colMax = new int[n];

        Map<Integer, List<int[]>> valueCellsMap = new TreeMap<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                valueCellsMap.computeIfAbsent(matrix[i][j], k -> new ArrayList<>()).add(new int[]{i, j});
            }
        }

        int[][] result = new int[m][n];
        for (int value : valueCellsMap.keySet()) {
            List<int[]> cells = valueCellsMap.get(value);
            UnionFind uf = new UnionFind(m + n);

            for (int[] cell : cells) {
                int row = cell[0], col = cell[1];
                uf.union(row, col + m);
            }

            Map<Integer, Integer> parentRankMap = new HashMap<>();
            for (int[] cell : cells) {
                int row = cell[0], col = cell[1];
                int parent = uf.find(row);
                int rank = Math.max(rowMax[row], colMax[col]) + 1;
                parentRankMap.put(parent, Math.max(parentRankMap.getOrDefault(parent, 0), rank));
            }

            for (int[] cell : cells) {
                int row = cell[0], col = cell[1];
                int parent = uf.find(row);
                int rank = parentRankMap.get(parent);
                result[row][col] = rank;
                rowMax[row] = Math.max(rowMax[row], rank);
                colMax[col] = Math.max(colMax[col], rank);
            }
        }

        return result;                  
    }
}
