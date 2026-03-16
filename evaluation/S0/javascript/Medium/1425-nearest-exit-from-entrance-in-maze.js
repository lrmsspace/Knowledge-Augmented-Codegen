// Source: https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.') and walls (represented as '+'). You are also given the entrance of the maze, where entrance = [entrancerow, entrancecol] denotes the row and column of the cell you are initially standing at.
//
// In one step, you can move one cell up, down, left, or right. You cannot step into a cell with a wall, and you cannot step outside the maze. Your goal is to find the nearest exit from the entrance. An exit is defined as an empty cell that is at the border of the maze. The entrance does not count as an exit.
//
// Return the number of steps in the shortest path from the entrance to the nearest exit, or -1 if no such path exists.
//
// Example:
// Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
// Output: 1
// Explanation: There are 3 exits in this maze at [1,0], [0,2], and [2,3].
// Initially, you are at the entrance cell [1,2].
// - You can reach [1,0] by moving 2 steps left.
// - You can reach [0,2] by moving 1 step up.
// It is impossible to reach [2,3] from the entrance.
// Thus, the nearest exit is [0,2], which is 1 step away.
//
// Constraints:
// maze.length == m
// 	maze[i].length == n
// 	1 <= m, n <= 100
// 	maze[i][j] is either '.' or '+'.
// 	entrance.length == 2
// 	0 <= entrancerow < m
// 	0 <= entrancecol < n
// 	entrance will always be an empty cell.
//

/**
 * @param {character[][]} maze
 * @param {number[]} entrance
 * @return {number}
 */
var nearestExit = function(maze, entrance) {
    const m = maze.length;
    const n = maze[0].length;
    const directions = [[0,1],[1,0],[0,-1],[-1,0]];
    const queue = [];
    const visited = Array.from({ length: m }, () => Array(n).fill(false));
    queue.push([...entrance, 0]);
    visited[entrance[0]][entrance[1]] = true;

    while (queue.length > 0) {
        const [row, col, steps] = queue.shift();

        // Check if current position is an exit (but not the entrance)
        if ((row === 0 || row === m - 1 || col === 0 || col === n - 1) && (row !== entrance[0] || col !== entrance[1])) {
            return steps;
        }

        for (const [dr, dc] of directions) {
            const newRow = row + dr;
            const newCol = col + dc;

            if (
                newRow >= 0 && newRow < m &&
                newCol >= 0 && newCol < n &&
                maze[newRow][newCol] === '.' &&
                !visited[newRow][newCol]
            ) {
                visited[newRow][newCol] = true;
                queue.push([newRow, newCol, steps + 1]);
            }
        }
    }

    return -1;
};