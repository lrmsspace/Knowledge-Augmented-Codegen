// Source: https://leetcode.com/problems/number-of-valid-move-combinations-on-chessboard/   |   Difficulty: Hard
//
// Problem Description:
// There is an 8 x 8 chessboard containing n pieces (rooks, queens, or bishops). You are given a string array pieces of length n, where pieces[i] describes the type (rook, queen, or bishop) of the ith piece. In addition, you are given a 2D integer array positions also of length n, where positions[i] = [ri, ci] indicates that the ith piece is currently at the 1-based coordinate (ri, ci) on the chessboard.
//
// When making a move for a piece, you choose a destination square that the piece will travel toward and stop on.
//
//
// 	A rook can only travel horizontally or vertically from (r, c) to the direction of (r+1, c), (r-1, c), (r, c+1), or (r, c-1).
// 	A queen can only travel horizontally, vertically, or diagonally from (r, c) to the direction of (r+1, c), (r-1, c), (r, c+1), (r, c-1), (r+1, c+1), (r+1, c-1), (r-1, c+1), (r-1, c-1).
// 	A bishop can only travel diagonally from (r, c) to the direction of (r+1, c+1), (r+1, c-1), (r-1, c+1), (r-1, c-1).
//
//
// You must make a move for every piece on the board simultaneously. A move combination consists of all the moves performed on all the given pieces. Every second, each piece will instantaneously travel one square towards their destination if they are not already at it. All pieces start traveling at the 0th second. A move combination is invalid if, at a given time, two or more pieces occupy the same square.
//
// Return the number of valid move combinations​​​​​.
//
//
// Example:
// Input: pieces = ["rook"], positions = [[1,1]]
// Output: 15
// Explanation: The image above shows the possible squares the piece can move to.
//
// Constraints:
// n == pieces.length 
// 	n == positions.length
// 	1 <= n <= 4
// 	pieces only contains the strings "rook", "queen", and "bishop".
// 	There will be at most one queen on the chessboard.
// 	1 <= ri, ci <= 8
// 	Each positions[i] is distinct.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        const int directions[3][8][2] = {
            {{1,0},{-1,0},{0,1},{0,-1}}, // Rook
            {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}}, // Queen
            {{1,1},{1,-1},{-1,1},{-1,-1}} // Bishop
        };
        
        int n = pieces.size();
        vector<vector<pair<int,int>>> moves(n);
        
        // Generate all possible moves for each piece
        for (int i = 0; i < n; i++) {
            int r = positions[i][0];
            int c = positions[i][1];
            int type = (pieces[i] == "rook") ? 0 : (pieces[i] == "queen") ? 1 : 2;
            
            for (const auto& dir : directions[type]) {
                int dr = dir[0];
                int dc = dir[1];
                int nr = r + dr;
                int nc = c + dc;
                
                while (nr >= 1 && nr <= 8 && nc >= 1 && nc <= 8) {
                    moves[i].emplace_back(nr, nc);
                    nr += dr;
                    nc += dc;
                }
            }
        }
        
        int validCombinations = 0;
        vector<int> indices(n, 0);
        
        // Backtracking to count valid combinations
        function<void(int)> backtrack = [&](int idx) {
            if (idx == n) {
                validCombinations++;
                return;
            }
            
            for (const auto& move : moves[idx]) {
                bool conflict = false;
                for (int j = 0; j < idx; j++) {
                    if (move == moves[j][indices[j]]) {
                        conflict = true;
                        break;
                    }
                }
                
                if (!conflict) {
                    indices[idx] = &move - &moves[idx][0];
                    backtrack(idx + 1);
                }
            }
        };
        
        backtrack(0);
        return validCombinations;
    }
};
