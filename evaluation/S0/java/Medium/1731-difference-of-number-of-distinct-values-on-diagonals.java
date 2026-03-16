// Source: https://leetcode.com/problems/difference-of-number-of-distinct-values-on-diagonals/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid of size m x n, you should find the matrix answer of size m x n.
//
// The cell answer[r][c] is calculated by looking at the diagonal values of the cell grid[r][c]:
//
//
// 	Let leftAbove[r][c] be the number of distinct values on the diagonal to the left and above the cell grid[r][c] not including the cell grid[r][c] itself.
// 	Let rightBelow[r][c] be the number of distinct values on the diagonal to the right and below the cell grid[r][c], not including the cell grid[r][c] itself.
// 	Then answer[r][c] = |leftAbove[r][c] - rightBelow[r][c]|.
//
//
// A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until the end of the matrix is reached.
//
//
// 	For example, in the below diagram the diagonal is highlighted using the cell with indices (2, 3) colored gray:
//
// 	
// 		Red-colored cells are left and above the cell.
// 		Blue-colored cells are right and below the cell.
// 	
// 	
//
//
//
//
// Return the matrix answer.
//
// Example:
// Input: grid = [[1,2,3],[3,1,5],[3,2,1]]
//
// Output: Output: [[1,1,0],[1,0,1],[0,1,1]]
//
// Explanation:
//
// To calculate the answer cells:
//
//
// 	
// 		
// 			answer
// 			left-above elements
// 			leftAbove
// 			right-below elements
// 			rightBelow
// 			|leftAbove - rightBelow|
// 		
// 	
// 	
// 		
// 			[0][0]
// 			[]
// 			0
// 			[grid[1][1], grid[2][2]]
// 			|{1, 1}| = 1
// 			1
// 		
// 		
// 			[0][1]
// 			[]
// 			0
// 			[grid[1][2]]
// 			|{5}| = 1
// 			1
// 		
// 		
// 			[0][2]
// 			[]
// 			0
// 			[]
// 			0
// 			0
// 		
// 		
// 			[1][0]
// 			[]
// 			0
// 			[grid[2][1]]
// 			|{2}| = 1
// 			1
// 		
// 		
// 			[1][1]
// 			[grid[0][0]]
// 			|{1}| = 1
// 			[grid[2][2]]
// 			|{1}| = 1
// 			0
// 		
// 		
// 			[1][2]
// 			[grid[0][1]]
// 			|{2}| = 1
// 			[]
// 			0
// 			1
// 		
// 		
// 			[2][0]
// 			[]
// 			0
// 			[]
// 			0
// 			0
// 		
// 		
// 			[2][1]
// 			[grid[1][0]]
// 			|{3}| = 1
// 			[]
// 			0
// 			1
// 		
// 		
// 			[2][2]
// 			[grid[0][0], grid[1][1]]
// 			|{1, 1}| = 1
// 			[]
// 			0
// 			1
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n, grid[i][j] <= 50
//

class Solution {
    public int[][] differenceOfDistinctValues(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int[][] leftAbove = new int[m][n];
        int[][] rightBelow = new int[m][n];

        // Calculate leftAbove
        for (int d = 0; d < m + n - 1; d++) {
            Set<Integer> seen = new HashSet<>();
            for (int i = 0; i < m; i++) {
                int j = d - i;
                if (j < 0 || j >= n) continue;

                leftAbove[i][j] = seen.size();
                seen.add(grid[i][j]);
            }
        }

        // Calculate rightBelow
        for (int d = 0; d < m + n - 1; d++) {
            Set<Integer> seen = new HashSet<>();
            for (int i = m - 1; i >= 0; i--) {
                int j = d - i;
                if (j < 0 || j >= n) continue;

                rightBelow[i][j] = seen.size();
                seen.add(grid[i][j]);
            }
        }

        // Calculate the answer
        int[][] answer = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                answer[i][j] = Math.abs(leftAbove[i][j] - rightBelow[i][j]);
            }
        }

        return answer;          
    }
}
