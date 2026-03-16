// Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/   |   Difficulty: Medium
//
// Problem Description:
// There is a dungeon with n x m rooms arranged as a grid.
//
// You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.
//
// Return the minimum time to reach the room (n - 1, m - 1).
//
// Two rooms are adjacent if they share a common wall, either horizontally or vertically.
//
// Example:
// Input: moveTime = [[0,4],[4,4]]
//
// Output: 7
//
// Explanation:
//
// The minimum time required is 7 seconds.
//
//
// 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
// 	At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.
//
// Constraints:
// 2 <= n == moveTime.length <= 750
// 	2 <= m == moveTime[i].length <= 750
// 	0 <= moveTime[i][j] <= 109
//

/**
 * @param {number[][]} moveTime
 * @return {number}
 */
var minTimeToReach = function(moveTime) {
    const n = moveTime.length;
    const m = moveTime[0].length;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const visited = Array.from({ length: n }, () => Array(m).fill(false));
    const queue = [[0, 0, 0, 0]]; // [x, y, time, moveCount]

    while (queue.length > 0) {
        const [x, y, time, moveCount] = queue.shift();
        if (x === n - 1 && y === m - 1) {
            return time;
        }
        for (const [dx, dy] of directions) {
            const nx = x + dx;
            const ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {   
                const nextTime = Math.max(time + (moveCount % 2 === 0 ? 1 : 2), moveTime[nx][ny]);
                visited[nx][ny] = true;
                queue.push([nx, ny, nextTime, moveCount + 1]);
            }
        }
    }
    return -1;
};
