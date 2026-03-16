// Source: https://leetcode.com/problems/construct-product-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size n * m as the product matrix of grid if the following condition is met:
//
//
// 	Each element p[i][j] is calculated as the product of all elements in grid except for the element grid[i][j]. This product is then taken modulo 12345.
//
//
// Return the product matrix of grid.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: [[24,12],[8,6]]
// Explanation: p[0][0] = grid[0][1] * grid[1][0] * grid[1][1] = 2 * 3 * 4 = 24
// p[0][1] = grid[0][0] * grid[1][0] * grid[1][1] = 1 * 3 * 4 = 12
// p[1][0] = grid[0][0] * grid[0][1] * grid[1][1] = 1 * 2 * 4 = 8
// p[1][1] = grid[0][0] * grid[0][1] * grid[1][0] = 1 * 2 * 3 = 6
// So the answer is [[24,12],[8,6]].
//
// Constraints:
// 1 <= n == grid.length <= 105
// 	1 <= m == grid[i].length <= 105
// 	2 <= n * m <= 105
// 	1 <= grid[i][j] <= 109
//

class Solution {
    public int[][] constructProductMatrix(int[][] grid) {
        int mod = 12345;
        long totalProduct = 1;
        int n = grid.length;
        int m = grid[0].length;

        // Calculate the total product of all elements in the grid modulo 12345
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                totalProduct = (totalProduct * (grid[i][j] % mod)) % mod;
            }
        }

        // Construct the product matrix
        int[][] productMatrix = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Calculate the product excluding grid[i][j]
                long element = grid[i][j] % mod;
                long inverseElement = modInverse(element, mod);
                productMatrix[i][j] = (int)((totalProduct * inverseElement) % mod);
            }
        }

        return productMatrix;           
    }
}
