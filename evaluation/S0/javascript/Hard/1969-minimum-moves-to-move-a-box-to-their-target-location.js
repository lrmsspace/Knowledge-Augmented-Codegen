// Source: https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/   |   Difficulty: Hard
//
// Problem Description:
// A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
//
// The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
//
// Your task is to move the box 'B' to the target position 'T' under the following rules:
//
//
// 	The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
// 	The character '.' represents the floor which means a free cell to walk.
// 	The character '#' represents the wall which means an obstacle (impossible to walk there).
// 	There is only one box 'B' and one target cell 'T' in the grid.
// 	The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
// 	The player cannot walk through the box.
//
//
// Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [["#","#","#","#","#","#"],
//                ["#","T","#","#","#","#"],
//                ["#",".",".","B",".","#"],
//                ["#",".","#","#",".","#"],
//                ["#",".",".",".","S","#"],
//                ["#","#","#","#","#","#"]]
// Output: 3
// Explanation: We return only the number of times the box is pushed.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	grid contains only characters '.', '#', 'S', 'T', or 'B'.
// 	There is only one character 'S', 'B', and 'T' in the grid.
//

/**
 * @param {character[][]} grid
 * @return {number}
 */
var minPushBox = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    let playerX, playerY, boxX, boxY, targetX, targetY;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 'S') {
                playerX = i;
                playerY = j;
            }
            else if (grid[i][j] === 'B') {
                boxX = i;
                boxY = j;
            }
            else if (grid[i][j] === 'T') {
                targetX = i;
                targetY = j;
            }
        }
    }
    const queue = [];
    const visited = new Set();
    const initialState = (playerX << 24) | (playerY << 16) | (boxX << 8) | boxY;
    queue.push(initialState);
    visited.add(initialState);
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    let pushes = 0;

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const state = queue.shift();
            const playerX = (state >> 24) & 0xFF;
            const playerY = (state >> 16) & 0xFF;
            const boxX = (state >> 8) & 0xFF;
            const boxY = state & 0xFF;
            if (boxX === targetX && boxY === targetY) {
                return pushes;
            }
            for (const [dx, dy] of directions) {
                const newPlayerX = playerX + dx;
                const newPlayerY = playerY + dy;
                if (newPlayerX >= 0 && newPlayerX < m && newPlayerY >= 0 && newPlayerY < n && grid[newPlayerX][newPlayerY] !== '#') {
                    if (newPlayerX === boxX && newPlayerY === boxY) {
                        const newBoxX = boxX + dx;
                        const newBoxY = boxY + dy;
                        if (newBoxX >= 0 && newBoxX < m && newBoxY >= 0 && newBoxY < n && grid[newBoxX][newBoxY] !== '#') {
                            const newState = (newPlayerX << 24) | (newPlayerY << 16) | (newBoxX << 8) | newBoxY;
                            if (!visited.has(newState)) {
                                visited.add(newState);
                                queue.push(newState);
                            }
                        }
                    } else {
                        const newState = (newPlayerX << 24) | (newPlayerY << 16) | (boxX << 8) | boxY;
                        if (!visited.has(newState)) {
                            visited.add(newState);
                            queue.push(newState);
                        }
                    }
                }
            }
        }
        pushes++;
    }
    return -1; // If we exhaust the queue without finding the target
};
