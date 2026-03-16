// Source: https://leetcode.com/problems/maximal-rectangle/   |   Difficulty: Hard
//
// Problem Description:
// Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
//
// Example:
// Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 6
// Explanation: The maximal rectangle is shown in the above picture.
//
// Constraints:
// rows == matrix.length
// 	cols == matrix[i].length
// 	1 <= row, cols <= 200
// 	matrix[i][j] is '0' or '1'.
//

/**
 * @param {character[][]} matrix
 * @return {number}
 */
var maximalRectangle = function(matrix) {
        

    if (matrix.length === 0) return 0;

    const rows = matrix.length;
    const cols = matrix[0].length;

    const heights = new Array(cols).fill(0);
    let maxArea = 0;
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            heights[j] = matrix[i][j] === '1' ? heights[j] + 1 : 0;
        }

        const stack = [];
        for (let j = 0; j <= cols; j++) {
            const currentHeight = j < cols ? heights[j] : 0;

            while (stack.length > 0 && currentHeight < heights[stack[stack.length - 1]]) {
                const height = heights[stack.pop()];
                const width = stack.length === 0 ? j : j - stack[stack.length - 1] - 1;
                maxArea = Math.max(maxArea, height * width);
            }

            stack.push(j);
        }
    }

    return maxArea; 
    
};
