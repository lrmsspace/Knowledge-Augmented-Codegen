// Source: https://leetcode.com/problems/maximum-number-of-moves-to-kill-all-pawns/   |   Difficulty: Hard
//
// Problem Description:
// There is a 50 x 50 chessboard with one knight and some pawns on it. You are given two integers kx and ky where (kx, ky) denotes the position of the knight, and a 2D array positions where positions[i] = [xi, yi] denotes the position of the pawns on the chessboard.
//
// Alice and Bob play a turn-based game, where Alice goes first. In each player's turn:
//
//
// 	The player selects a pawn that still exists on the board and captures it with the knight in the fewest possible moves. Note that the player can select any pawn, it might not be one that can be captured in the least number of moves.
// 	In the process of capturing the selected pawn, the knight may pass other pawns without capturing them. Only the selected pawn can be captured in this turn.
//
//
// Alice is trying to maximize the sum of the number of moves made by both players until there are no more pawns on the board, whereas Bob tries to minimize them.
//
// Return the maximum total number of moves made during the game that Alice can achieve, assuming both players play optimally.
//
// Note that in one move, a chess knight has eight possible positions it can move to, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.
//
// Example:
// Input: kx = 1, ky = 1, positions = [[0,0]]
//
// Output: 4
//
// Explanation:
//
//
//
// The knight takes 4 moves to reach the pawn at (0, 0).
//
// Constraints:
// 0 <= kx, ky <= 49
// 	1 <= positions.length <= 15
// 	positions[i].length == 2
// 	0 <= positions[i][0], positions[i][1] <= 49
// 	All positions[i] are unique.
// 	The input is generated such that positions[i] != [kx, ky] for all 0 <= i < positions.length.
//

int maxMoves(int kx, int ky, int** positions, int positionsSize, int* positionsColSize) {
    int n = positionsSize;
    int dist[16][16];
    int moves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    
    // Precompute distances between all pairs of positions (including knight's start position)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = INT_MAX;
        }
        dist[i][n] = INT_MAX; // distance from knight's start to pawn i
    }
    
    for (int i = 0; i < n; ++i) {
        // BFS to compute distance from knight's start to pawn i
        int visited[50][50] = {0};
        int queue[2500][3];
        int front = 0, back = 0;
        queue[back][0] = kx;
        queue[back][1] = ky;
        queue[back++][2] = 0;
        visited[kx][ky] = 1;
        
        while (front < back) {
            int x = queue[front][0];
            int y = queue[front][1];
            int d = queue[front++][2];
            
            if (x == positions[i][0] && y == positions[i][1]) {
                dist[n][i] = d;
                break;
            }
            
            for (int m = 0; m < 8; ++m) {
                int nx = x + moves[m][0];
                int ny = y + moves[m][1];
                if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && !visited[nx][ny]) {
                    visited[nx][ny] = 1;
                    queue[back][0] = nx;
                    queue[back][1] = ny;
                    queue[back++][2] = d + 1;
                }
            }
        }
        
        // BFS to compute distances between pawns
        visited[50][50] = {0};
        front = 0; back = 0;
        queue[back][0] = positions[i][0];
        queue[back][1] = positions[i][1];
        queue[back++][2] = 0;
        visited[positions[i][0]][positions[i][1]] = 1;

        while (front < back) {
            int x = queue[front][0];
            int y = queue[front][1];
            int d = queue[front++][2];
            
            for (int m = 0; m < 8; ++m) {
                int nx = x + moves[m][0];
                int ny = y + moves[m][1];
                if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && !visited[nx][ny]) {
                    visited[nx][ny] = 1;
                    queue[back][0] = nx;
                    queue[back][1] = ny;
                    queue[back++][2] = d + 1;
                    
                    for (int j = 0; j < n; ++j) {
                        if (nx == positions[j][0] && ny == positions[j][1]) {
                            dist[i][j] = d + 1;
                        }
                    }
                }
            }
        }
    }
    // DP to find maximum moves
    int dp[1 << 15][15];
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        if (dist[n][i] != INT_MAX) {
            dp[1 << i][i] = dist[n][i];
        }
    }
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (dp[mask][u] == -1) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v)) && dist[u][v] != INT_MAX) {
                    int nextMask = mask | (1 << v);
                    int nextDist = dp[mask][u] + dist[u][v];
                    if (dp[nextMask][v] == -1 || dp[nextMask][v] < nextDist) {
                        dp[nextMask][v] = nextDist;
                    }
                }
            }
        }
    }
    int maxMoves = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (dp[mask][u] != -1) {
                if (dp[mask][u] > maxMoves) {
                    maxMoves = dp[mask][u];
                }
            }
        }
    }
    return maxMoves;
}
