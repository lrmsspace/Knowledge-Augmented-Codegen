// Source: https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbors of it if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighbors if they share one edge.
//
// Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.
//
// A binary matrix is a matrix with all cells equal to 0 or 1 only.
//
// A zero matrix is a matrix with all cells equal to 0.
//
// Example:
// Input: mat = [[0,0],[0,1]]
// Output: 3
// Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 3
// 	mat[i][j] is either 0 or 1.
//

int minFlips(int** mat, int matSize, int* matColSize) {
    int rows = matSize, cols = matColSize[0];
    int total = 1 << (rows * cols);
    int dist[total];
    memset(dist, -1, sizeof(dist));
    int start = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (mat[r][c]) {
                start |= 1 << (r * cols + c);
            }
        }
    }

    int queue[total];
    int front = 0, back = 0;
    queue[back++] = start;
    dist[start] = 0;

    int directions[5] = {0, 1, 0, -1, 0};

    while (front < back) {
        int state = queue[front++];
        if (state == 0) return dist[state];

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int nextState = state;
                for (int d = 0; d < 5; ++d) {
                    int nr = r + directions[d];
                    int nc = c + directions[d + 1];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        nextState ^= 1 << (nr * cols + nc);
                    }
                }
                if (dist[nextState] == -1) {
                    dist[nextState] = dist[state] + 1;
                    queue[back++] = nextState;
                }
            }
        }
    }

    return -1;      
}
