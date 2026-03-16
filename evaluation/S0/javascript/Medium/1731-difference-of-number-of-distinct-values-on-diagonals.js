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

/**
 * @param {number[][]} grid
 * @return {number[][]}
 */
var differenceOfDistinctValues = function(grid) {
    const m = grid.length;  
    const n = grid[0].length;   
    const answer = Array.from({ length: m }, () => Array(n).fill(0));

    // Process diagonals starting from the first column
    for (let row = 0; row < m; row++) {
        let r = row;
        let c = 0;
        const leftAboveSet = new Set();
        const rightBelowSet = new Set();
        const diagonalElements = [];

        // Collect diagonal elements
        while (r < m && c < n) {
            diagonalElements.push([r, c]);
            r++;
            c++;
        }
        // Calculate rightBelow counts
        for (let i = diagonalElements.length - 1; i >= 0; i--) {
            const [dr, dc] = diagonalElements[i];
            answer[dr][dc] = Math.abs(leftAboveSet.size - rightBelowSet.size);
            rightBelowSet.add(grid[dr][dc]);
        }
        // Update leftAbove counts
        for (let i = 0; i < diagonalElements.length; i++) {
            const [dr, dc] = diagonalElements[i];
            leftAboveSet.add(grid[dr][dc]);
        }
    }

    // Process diagonals starting from the first row (excluding the top-left cell)
    for (let col = 1; col < n; col++) {
        let r = 0;
        let c = col;
        const leftAboveSet = new Set();
        const rightBelowSet = new Set();
        const diagonalElements = [];
        // Collect diagonal elements
        while (r < m && c < n) {
            diagonalElements.push([r, c]);
            r++;
            c++;
        }
        // Calculate rightBelow counts  
        for (let i = diagonalElements.length - 1; i >= 0; i--) {
            const [dr, dc] = diagonalElements[i];
            answer[dr][dc] = Math.abs(leftAboveSet.size - rightBelowSet.size);
            rightBelowSet.add(grid[dr][dc]);
        }
        // Update leftAbove counts
        for (let i = 0; i < diagonalElements.length; i++) {
            const [dr, dc] = diagonalElements[i];
            leftAboveSet.add(grid[dr][dc]);
        }
    }

    return answer;  
};
