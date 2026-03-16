// Source: https://leetcode.com/problems/word-search/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n grid of characters board and a string word, return true if word exists in the grid.
//
// The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.
//
// Example:
// Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
// Output: true
//
// Constraints:
// m == board.length
// 	n = board[i].length
// 	1 <= m, n <= 6
// 	1 <= word.length <= 15
// 	board and word consists of only lowercase and uppercase English letters.
//
//
//  
// Follow up: Could you use search pruning to make your solution faster with a larger board?
//

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        function<bool(int, int, int)> dfs = [&](int r, int c, int index) {
            if (index == word.size()) return true;
            if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
            if (visited[r][c] || board[r][c] != word[index]) return false;

            visited[r][c] = true;
            bool found = dfs(r + 1, c, index + 1) ||
                         dfs(r - 1, c, index + 1) ||
                         dfs(r, c + 1, index + 1) ||
                         dfs(r, c - 1, index + 1);
            visited[r][c] = false;

            return found;
        };

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (dfs(r, c, 0)) return true;
            }
        }

        return false;           
    }
};
