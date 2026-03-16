// Source: https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/   |   Difficulty: Hard
//
// Problem Description:
// In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
//
// In one move the snake can:
//
//
// 	Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
// 	
// 	Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
// 	
//
//
// Return the minimum number of moves to reach the target.
//
// If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [[0,0,0,0,0,1],
//                [1,1,0,0,1,0],
//                [0,0,0,0,1,1],
//                [0,0,1,0,1,0],
//                [0,1,1,0,0,0],
//                [0,1,1,0,0,0]]
// Output: 11
// Explanation:
// One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
//
// Constraints:
// 2 <= n <= 100
// 	0 <= grid[i][j] <= 1
// 	It is guaranteed that the snake starts at empty cells.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minimumMoves = function(grid) {
    const n = grid.length;
    const queue = [[0, 0, 0]];
    const visited = new Set();
    visited.add('0,0,0');
    const target = `${n-1},${n-2},0`;
    const targetRotated = `${n-1},${n-2},1`;
    let moves = 0;

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const [r, c, orientation] = queue.shift();
            const state = `${r},${c},${orientation}`;
            if (state === target || state === targetRotated) {
                return moves;
            }
            // Move right
            if (orientation === 0 && c + 2 < n && grid[r][c + 2] === 0) {
                const nextState = `${r},${c + 1},0`;
                if (!visited.has(nextState)) {
                    visited.add(nextState);
                    queue.push([r, c + 1, 0]);
                }
            }
            // Move down
            if (orientation === 1 && r + 2 < n && grid[r + 2][c] === 0) {
                const nextState = `${r + 1},${c},1`;
                if (!visited.has(nextState)) {
                    visited.add(nextState);
                    queue.push([r + 1, c, 1]);
                }
            }
            // Rotate clockwise
            if (orientation === 0 && r + 1 < n && grid[r + 1][c] === 0 && grid[r + 1][c + 1] === 0) {
                const nextState = `${r},${c},1`;
                if (!visited.has(nextState)) {
                    visited.add(nextState);
                    queue.push([r, c, 1]);
                }
            }
            // Rotate counterclockwise  
            if (orientation === 1 && c + 1 < n && grid[r][c + 1] === 0 && grid[r + 1][c + 1] === 0) {
                const nextState = `${r},${c},0`;
                if (!visited.has(nextState)) {
                    visited.add(nextState);
                    queue.push([r, c, 0]);
                }
            }
        }
        moves++;
    }
    return -1;  
};
