// Source: https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:
//
//
// 	'S': Starting position of the student
// 	'L': Litter that must be collected (once collected, the cell becomes empty)
// 	'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
// 	'X': Obstacle the student cannot pass through
// 	'.': Empty space
//
//
// You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.
//
// Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.
//
// Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.
//
// Example:
// Input: classroom = ["S.", "XL"], energy = 2
//
// Output: 2
//
// Explanation:
//
//
// 	The student starts at cell (0, 0) with 2 units of energy.
// 	Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
// 	A valid sequence of moves to collect all litter is as follows:
// 	
// 		Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
// 		Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
// 	
// 	
// 	The student collects all the litter using 2 moves. Thus, the output is 2.
//
// Constraints:
// 1 <= m == classroom.length <= 20
// 	1 <= n == classroom[i].length <= 20
// 	classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
// 	1 <= energy <= 50
// 	There is exactly one 'S' in the grid.
// 	There are at most 10 'L' cells in the grid.
//

/**
 * @param {string[]} classroom
 * @param {number} energy
 * @return {number}
 */
var minMoves = function(classroom, energy) {
    const m = classroom.length;
    const n = classroom[0].length;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    let startX, startY;
    const litterPositions = [];
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (classroom[i][j] === 'S') {
                startX = i;
                startY = j;
            } else if (classroom[i][j] === 'L') {
                litterPositions.push([i, j]);
            }
        }
    }   
    const totalLitter = litterPositions.length;
    const queue = [[startX, startY, energy, 0, 0]]; // [x, y, remainingEnergy, moves, collectedLitterMask]
    const visited = new Set();
    visited.add(`${startX},${startY},${energy},0`);
    while (queue.length > 0) {
        const [x, y, remainingEnergy, moves, collectedLitterMask] = queue.shift();
        if (collectedLitterMask === (1 << totalLitter) - 1) {
            return moves;
        }
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && classroom[newX][newY] !== 'X') {
                let newEnergy = remainingEnergy - 1;
                let newCollectedLitterMask = collectedLitterMask;
                if (classroom[newX][newY] === 'R') {
                    newEnergy = energy;
                }
                for (let i = 0; i < totalLitter; i++) {
                    if (newX === litterPositions[i][0] && newY === litterPositions[i][1]) {
                        newCollectedLitterMask |= (1 << i);
                        break;
                    }
                }
                const stateKey = `${newX},${newY},${newEnergy},${newCollectedLitterMask}`;
                if (!visited.has(stateKey)) {
                    visited.add(stateKey);
                    queue.push([newX, newY, newEnergy, moves + 1, newCollectedLitterMask]);
                }
            }
        }
    }
    return -1;  
};
