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

class Solution {
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        const int n = positions.size();
        const vector<pair<int, int>> directions = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        
        // Precompute distances from knight to each pawn
        vector<int> distToPawn(n, INT_MAX);
        for (int i = 0; i < n; ++i) {
            queue<pair<int, int>> q;
            vector<vector<bool>> visited(50, vector<bool>(50, false));
            q.push({kx, ky});
            visited[kx][ky] = true;
            int moves = 0;
            bool found = false;
            
            while (!q.empty() && !found) {
                int size = q.size();
                for (int j = 0; j < size; ++j) {
                    auto [x, y] = q.front(); q.pop();
                    if (x == positions[i][0] && y == positions[i][1]) {
                        distToPawn[i] = moves;
                        found = true;
                        break;
                    }
                    for (const auto& dir : directions) {
                        int nx = x + dir.first;
                        int ny = y + dir.second;
                        if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && !visited[nx][ny]) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
                moves++;
            }
        }
        
        // DP with bitmasking
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MIN));
        
        // Initialize dp for single pawn captures
        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = distToPawn[i];
        }
        
        // Fill dp table
        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int last = 0; last < n; ++last) {
                if (!(mask & (1 << last)) || dp[mask][last] == INT_MIN) continue;
                
                for (int next = 0; next < n; ++next) {
                    if (mask & (1 << next)) continue;
                    
                    // Calculate distance from last pawn to next pawn
                    queue<pair<int, int>> q;
                    vector<vector<bool>> visited(50, vector<bool>(50, false));
                    q.push({positions[last][0], positions[last][1]});
                    visited[positions[last][0]][positions[last][1]] = true;
                    int moves = 0;
                    bool found = false;
                    
                    while (!q.empty() && !found) {
                        int size = q.size();
                        for (int j = 0; j < size; ++j) {
                            auto [x, y] = q.front(); q.pop();
                            if (x == positions[next][0] && y == positions[next][1]) {
                                dp[mask | (1 << next)][next] = max(dp[mask | (1 << next)][next], dp[mask][last] + moves);
                                found = true;
                                break;
                            }
                            for (const auto& dir : directions) {
                                int nx = x + dir.first;
                                int ny = y + dir.second;
                                if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && !visited[nx][ny]) {
                                    visited[nx][ny] = true;
                                    q.push({nx, ny});
                                }
                            }
                        }
                        moves++;
                    }
                }
            }
        }
        
        int maxMoves = 0;
        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int last = 0; last < n; ++last) {
                if (dp[mask][last] != INT_MIN) {
                    maxMoves = max(maxMoves, dp[mask][last]);
                }
            }
        }
        
        return maxMoves;
    }
};
