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
// Helpful references (internal KB):
// - Breadth-first search (graph, array, stack, bfs, enumeration)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
//   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
//   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
//   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} classroom
 * @param {number} energy
 * @return {number}
 */
var minMoves = function(classroom, energy) {
    const m = classroom.length;
    const n = classroom[0].length;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const visited = new Set();
    const portals = {};
    
    // Collect portal locations
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const cell = classroom[i][j];
            if (cell >= 'A' && cell <= 'Z') {
                if (!portals[cell]) {
                    portals[cell] = [];
                }
                portals[cell].push([i, j]);
            }
        }
    }
    
    let startX, startY;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (classroom[i][j] === 'S') {
                startX = i;
                startY = j;
                break;
            }
        }
    }
    
    const queue = [[startX, startY, energy, 0]]; // [x, y, remainingEnergy, moves]
    visited.add(`${startX},${startY},${energy}`);
    
    while (queue.length > 0) {
        const [x, y, remainingEnergy, moves] = queue.shift();
        
        if (classroom[x][y] === 'L') {
            return moves;
        }
        
        // Check adjacent cells
        for (const [dx, dy] of directions) {
            const nx = x + dx;
            const ny = y + dy;
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] !== '#' && remainingEnergy > 0) {
                const newEnergy = classroom[nx][ny] === 'R' ? energy : remainingEnergy - 1;
                const stateKey = `${nx},${ny},${newEnergy}`;
                
                if (!visited.has(stateKey)) {
                    visited.add(stateKey);
                    queue.push([nx, ny, newEnergy, moves + 1]);
                }
            }
        }
        
        // Check for teleportation
        const cell = classroom[x][y];
        if (cell >= 'A' && cell <= 'Z' && portals[cell]) {
            for (const [px, py] of portals[cell]) {
                const newEnergy = classroom[px][py] === 'R' ? energy : remainingEnergy;
                const stateKey = `${px},${py},${newEnergy}`;
                if (!visited.has(stateKey)) {
                    visited.add(stateKey);
                    queue.push([px, py, newEnergy, moves]); // Teleportation does not count as a move
                }
            }
            delete portals[cell]; // Remove the portal to prevent reuse
        }
    }
    
    return -1; // Destination not reachable
};
