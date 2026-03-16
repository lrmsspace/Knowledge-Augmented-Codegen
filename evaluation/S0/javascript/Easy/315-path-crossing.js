// Source: https://leetcode.com/problems/path-crossing/   |   Difficulty: Easy
//
// Problem Description:
// Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.
//
// Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.
//
// Example:
// Input: path = "NES"
// Output: false 
// Explanation: Notice that the path doesn't cross any point more than once.
//
// Constraints:
// 1 <= path.length <= 104
// 	path[i] is either 'N', 'S', 'E', or 'W'.
//

/**
 * @param {string} path
 * @return {boolean}
 */
var isPathCrossing = function(path) {
    const visited = new Set();
    let x = 0, y = 0;
    visited.add(`${x},${y}`);
    for (const direction of path) {
        if (direction === 'N') y++;
        else if (direction === 'S') y--;
        else if (direction === 'E') x++;
        else if (direction === 'W') x--;
        const pos = `${x},${y}`;
        if (visited.has(pos)) {
            return true;
        }
        visited.add(pos);
    }
    return false;
};