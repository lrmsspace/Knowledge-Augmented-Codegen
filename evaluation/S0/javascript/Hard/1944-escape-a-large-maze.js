// Source: https://leetcode.com/problems/escape-a-large-maze/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1 million by 1 million grid on an XY-plane, and the coordinates of each grid square are (x, y).
//
// We start at the source = [sx, sy] square and want to reach the target = [tx, ty] square. There is also an array of blocked squares, where each blocked[i] = [xi, yi] represents a blocked square with coordinates (xi, yi).
//
// Each move, we can walk one square north, east, south, or west if the square is not in the array of blocked squares. We are also not allowed to walk outside of the grid.
//
// Return true if and only if it is possible to reach the target square from the source square through a sequence of valid moves.
//
// Example:
// Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
// Output: false
// Explanation: The target square is inaccessible starting from the source square because we cannot move.
// We cannot move north or east because those squares are blocked.
// We cannot move south or west because we cannot go outside of the grid.
//
// Constraints:
// 0 <= blocked.length <= 200
// 	blocked[i].length == 2
// 	0 <= xi, yi < 106
// 	source.length == target.length == 2
// 	0 <= sx, sy, tx, ty < 106
// 	source != target
// 	It is guaranteed that source and target are not blocked.
//

/**
 * @param {number[][]} blocked
 * @param {number[]} source
 * @param {number[]} target
 * @return {boolean}
 */
var isEscapePossible = function(blocked, source, target) {
    const blockedSet = new Set(blocked.map(([x, y]) => `${x},${y}`));
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    const bfs = (start, end) => {
        const queue = [start];
        const visited = new Set([`${start[0]},${start[1]}`]);
        while (queue.length > 0) {
            const [x, y] = queue.shift();
            if (x === end[0] && y === end[1]) {
                return true;
            }
            for (const [dx, dy] of directions) {
                const newX = x + dx;
                const newY = y + dy;
                const newPos = `${newX},${newY}`;
                if (newX >= 0 && newX < 1e6 && newY >= 0 && newY < 1e6 && !blockedSet.has(newPos) && !visited.has(newPos)) {
                    visited.add(newPos);
                    queue.push([newX, newY]);
                }
            }
            if (visited.size > 200) {
                return true; // If we have visited more than 200 squares, we can assume we can escape
            }
        }
        return false;
    }
    return bfs(source, target) && bfs(target, source);  
};
