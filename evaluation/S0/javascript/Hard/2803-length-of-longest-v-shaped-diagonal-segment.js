// Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
//
// A V-shaped diagonal segment is defined as:
//
//
// 	The segment starts with 1.
// 	The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
// 	The segment:
// 	
// 		Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
// 		Continues the sequence in the same diagonal direction.
// 		Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.
// 	
// 	
//
//
// Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
//
// Example:
// Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
//
// Output: 5
//
// Explanation:
//
//
//
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).
//
// Constraints:
// n == grid.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	grid[i][j] is either 0, 1 or 2.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var lenOfVDiagonal = function(grid) {
    const n = grid.length;
    const m = grid[0].length;
    const directions = [
        [[-1, -1], [1, 1]], // top-left to bottom-right
        [[-1, 1], [1, -1]], // top-right to bottom-left
        [[1, 1], [-1, -1]], // bottom-right to top-left
        [[1, -1], [-1, 1]]  // bottom-left to top-right
    ];
    const sequence = [1, 2, 0];
    let maxLength = 0;
    const isValid = (x, y) => x >= 0 && x < n && y >= 0 && y < m;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < m; j++) {
            if (grid[i][j] !== 1) continue;
            for (const dir of directions) {
                let length = 1;
                let x = i, y = j;
                let seqIndex = 1;
                let turned = false;
                while (true) {
                    const [dx, dy] = dir[turned ? 1 : 0];
                    const nx = x + dx;
                    const ny = y + dy;
                    if (isValid(nx, ny) && grid[nx][ny] === sequence[seqIndex]) {
                        length++;
                        x = nx;
                        y = ny;
                        seqIndex = (seqIndex + 1) % 3;
                    }
                    else if (!turned) {
                        turned = true;
                    }
                    else {
                        break;
                    }
                }
                maxLength = Math.max(maxLength, length);
            }
        }
    }
    return maxLength;   
};
