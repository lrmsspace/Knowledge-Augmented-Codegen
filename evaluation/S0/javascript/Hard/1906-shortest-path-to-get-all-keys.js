// Source: https://leetcode.com/problems/shortest-path-to-get-all-keys/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n grid grid where:
//
//
// 	'.' is an empty cell.
// 	'#' is a wall.
// 	'@' is the starting point.
// 	Lowercase letters represent keys.
// 	Uppercase letters represent locks.
//
//
// You start at the starting point and one move consists of walking one space in one of the four cardinal directions. You cannot walk outside the grid, or walk into a wall.
//
// If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.
//
// For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of the first k letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
//
// Return the lowest number of moves to acquire all keys. If it is impossible, return -1.
//
// Example:
// Input: grid = ["@.a..","###.#","b.A.B"]
// Output: 8
// Explanation: Note that the goal is to obtain all the keys not to open all the locks.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 30
// 	grid[i][j] is either an English letter, '.', '#', or '@'. 
// 	There is exactly one '@' in the grid.
// 	The number of keys in the grid is in the range [1, 6].
// 	Each key in the grid is unique.
// 	Each key in the grid has a matching lock.
//

/**
 * @param {string[]} grid
 * @return {number}
 */
var shortestPathAllKeys = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const queue = [];
    const visited = new Set();
    let allKeysMask = 0;        
    for (let i = 0; i < m; i++) {   
        for (let j = 0; j < n; j++) {
            const cell = grid[i][j];
            if (cell === '@') {
                const state = (0 << 16) | (i << 8) | j;
                queue.push(state);
                visited.add(state);
            }
            if (cell >= 'a' && cell <= 'f') {
                allKeysMask |= (1 << (cell.charCodeAt(0) - 'a'.charCodeAt(0)));
            }
        }
    }
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    let steps = 0;

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const state = queue.shift();
            const keysMask = (state >> 16) & 0xFF;
            const x = (state >> 8) & 0xFF;
            const y = state & 0xFF;
            if (keysMask === allKeysMask) {
                return steps;
            }
            for (const [dx, dy] of directions) {    
                const newX = x + dx;
                const newY = y + dy;
                if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                    const cell = grid[newX][newY];
                    if (cell !== '#') {
                        let newKeysMask = keysMask;
                        if (cell >= 'a' && cell <= 'f') {
                            newKeysMask |= (1 << (cell.charCodeAt(0) - 'a'.charCodeAt(0)));
                        }
                        if (cell >= 'A' && cell <= 'F') {
                            if ((newKeysMask & (1 << (cell.charCodeAt(0) - 'A'.charCodeAt(0)))) === 0) {
                                continue; // Skip if we don't have the key for this lock
                            }
                        }
                        const newState = (newKeysMask << 16) | (newX << 8) | newY;
                        if (!visited.has(newState)) {
                            visited.add(newState);
                            queue.push(newState);
                        }
                    }
                }
            }
        }
        steps++;
    }
    return -1; // If we exhaust the queue without finding all keys, return -1   
};
