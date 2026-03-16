// Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
//
//
// 	'.' representing an empty cell.
// 	'#' representing an obstacle.
// 	An uppercase letter ('A'-'Z') representing a teleportation portal.
//
//
// You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
//
// If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
//
// Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
//
// Example:
// Input: matrix = ["A..",".A.","..."]
//
// Output: 2
//
// Explanation:
//
//
//
//
// 	Before the first move, teleport from (0, 0) to (1, 1).
// 	In the first move, move from (1, 1) to (1, 2).
// 	In the second move, move from (1, 2) to (2, 2).
//
// Constraints:
// 1 <= m == matrix.length <= 103
// 	1 <= n == matrix[i].length <= 103
// 	matrix[i][j] is either '#', '.', or an uppercase English letter.
// 	matrix[0][0] is not an obstacle.
//

int minMoves(char** matrix, int matrixSize) {
    int n = strlen(matrix[0]);
    if (matrix[0][0] == '#' || matrix[matrixSize - 1][n - 1] == '#') return -1;

    typedef struct {
        int x, y, dist;
    } Node;

    Node queue[matrixSize * n];
    int front = 0, rear = 0;
    bool visited[matrixSize][n];
    memset(visited, false, sizeof(visited));
    visited[0][0] = true;

    // Store portal positions
    typedef struct {
        int positions[10000][2];
        int count;
    } Portal;

    Portal portals[26];
    for (int i = 0; i < 26; i++) portals[i].count = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < n; j++) {
            char c = matrix[i][j];
            if (c >= 'A' && c <= 'Z') {
                portals[c - 'A'].positions[portals[c - 'A'].count][0] = i;
                portals[c - 'A'].positions[portals[c - 'A'].count][1] = j;
                portals[c - 'A'].count++;
            }
        }
    }

    queue[rear++] = (Node){0, 0, 0};

    bool usedPortals[26];
    memset(usedPortals, false, sizeof(usedPortals));

    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (front < rear) {
        Node curr = queue[front++];
        if (curr.x == matrixSize - 1 && curr.y == n - 1) return curr.dist;

        // Move in 4 directions
        for (int d = 0; d < 4; d++) {
            int nx = curr.x + directions[d][0];
            int ny = curr.y + directions[d][1];
            if (nx >= 0 && nx < matrixSize && ny >= 0 && ny < n &&
                matrix[nx][ny] != '#' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                queue[rear++] = (Node){nx, ny, curr.dist + 1};
            }
        }

        // Teleportation
        char c = matrix[curr.x][curr.y];
        if (c >= 'A' && c <= 'Z' && !usedPortals[c - 'A']) {
            usedPortals[c - 'A'] = true;
            Portal portal = portals[c - 'A'];
            for (int i = 0; i < portal.count; i++) {
                int px = portal.positions[i][0];
                int py = portal.positions[i][1];
                if (!visited[px][py]) {
                    visited[px][py] = true;
                    queue[rear++] = (Node){px, py, curr.dist};
                }
            }
        }
    }
    return -1;
}
