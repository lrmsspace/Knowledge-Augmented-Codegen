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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minMoves(char** classroom, int classroomSize, int energy) {
    int m = classroomSize;
    int n = strlen(classroom[0]);
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    // Locate positions of S, L, and R
    int startX, startY;
    int litterCount = 0;
    int litterPositions[10][2];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (classroom[i][j] == 'S') {
                startX = i;
                startY = j;
            } else if (classroom[i][j] == 'L') {
                litterPositions[litterCount][0] = i;
                litterPositions[litterCount][1] = j;
                litterCount++;
            }
        }
    }

    // BFS to find minimum moves to collect all litter
    typedef struct {
        int x, y, energyLeft, moves, collectedMask;
    } State;

    int totalStates = m * n * (energy + 1) * (1 << litterCount);
    char *visited = (char*)calloc(totalStates, sizeof(char));
    State *queue = (State*)malloc(totalStates * sizeof(State));
    int front = 0, back = 0;

    State initialState = {startX, startY, energy, 0, 0};
    queue[back++] = initialState;
    visited[(startX * n + startY) * (energy + 1) * (1 << litterCount)] = 1;

    while (front < back) {
        State curr = queue[front++];
        
        // Check if all litter collected
        if (curr.collectedMask == (1 << litterCount) - 1) {
            free(visited);
            free(queue);
            return curr.moves;
        }

        // Explore neighbors
        for (int d = 0; d < 4; d++) {
            int newX = curr.x + directions[d][0];
            int newY = curr.y + directions[d][1];
            int newEnergy = curr.energyLeft - 1;

            if (newX < 0 || newX >= m || newY < 0 || newY >= n || classroom[newX][newY] == 'X') {
                continue; // Out of bounds or obstacle
            }
            if (newEnergy < 0) {
                continue; // Not enough energy to move
            }
            if (classroom[newX][newY] == 'R') {
                newEnergy = energy; // Reset energy
            }
            int newCollectedMask = curr.collectedMask;
            for (int i = 0; i < litterCount; i++) {
                if (newX == litterPositions[i][0] && newY == litterPositions[i][1]) {
                    newCollectedMask |= (1 << i); // Collect litter
                }
            }
            int stateIndex = (newX * n + newY) * (energy + 1) * (1 << litterCount) + newEnergy * (1 << litterCount) + newCollectedMask;
            if (!visited[stateIndex]) {
                visited[stateIndex] = 1;
                State newState = {newX, newY, newEnergy, curr.moves + 1, newCollectedMask};
                queue[back++] = newState;
            }
        }
    }
    free(visited);
    free(queue);
    return -1; // Impossible to collect all litter
}
