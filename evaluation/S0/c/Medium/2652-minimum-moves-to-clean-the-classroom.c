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

int minMoves(char** classroom, int classroomSize, int energy) {
    int m = classroomSize;
    int n = strlen(classroom[0]);
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    // Find positions of S, L, and R
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
    
    State queue[40000];
    int front = 0, rear = 0;
    bool visited[m][n][51][1 << litterCount];
    
    memset(visited, false, sizeof(visited));
    queue[rear++] = (State){startX, startY, energy, 0, 0};
    visited[startX][startY][energy][0] = true;
    
    while (front < rear) {
        State curr = queue[front++];
        
        // Check if all litter collected
        if (curr.collectedMask == (1 << litterCount) - 1) {
            return curr.moves;
        }
        
        for (int d = 0; d < 4; d++) {
            int newX = curr.x + directions[d][0];
            int newY = curr.y + directions[d][1];
            int newEnergy = curr.energyLeft - 1;
            int newCollectedMask = curr.collectedMask;
            
            if (newX < 0 || newX >= m || newY < 0 || newY >= n || classroom[newX][newY] == 'X') {
                continue; // Out of bounds or obstacle
            }
            
            if (newEnergy < 0) {
                continue; // Not enough energy
            }
            if (classroom[newX][newY] == 'R') {
                newEnergy = energy; // Reset energy
            }
            for (int i = 0; i < litterCount; i++) {
                if (newX == litterPositions[i][0] && newY == litterPositions[i][1]) {
                    newCollectedMask |= (1 << i); // Collect litter
                }
            }
            if (!visited[newX][newY][newEnergy][newCollectedMask]) {
                visited[newX][newY][newEnergy][newCollectedMask] = true;
                queue[rear++] = (State){newX, newY, newEnergy, curr.moves + 1, newCollectedMask};
            }
        }
    }
    return -1; // Impossible to collect all litter
}
