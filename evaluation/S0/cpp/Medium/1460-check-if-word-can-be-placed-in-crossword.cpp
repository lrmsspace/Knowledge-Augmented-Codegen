// Source: https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix board, representing the current state of a crossword puzzle. The crossword contains lowercase English letters (from solved words), ' ' to represent any empty cells, and '#' to represent any blocked cells.
//
// A word can be placed horizontally (left to right or right to left) or vertically (top to bottom or bottom to top) in the board if:
//
//
// 	It does not occupy a cell containing the character '#'.
// 	The cell each letter is placed in must either be ' ' (empty) or match the letter already on the board.
// 	There must not be any empty cells ' ' or other lowercase letters directly left or right of the word if the word was placed horizontally.
// 	There must not be any empty cells ' ' or other lowercase letters directly above or below the word if the word was placed vertically.
//
//
// Given a string word, return true if word can be placed in board, or false otherwise.
//
// Example:
// Input: board = [["#", " ", "#"], [" ", " ", "#"], ["#", "c", " "]], word = "abc"
// Output: true
// Explanation: The word "abc" can be placed as shown above (top to bottom).
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m * n <= 2 * 105
// 	board[i][j] will be ' ', '#', or a lowercase English letter.
// 	1 <= word.length <= max(m, n)
// 	word will contain only lowercase English letters.
//

class Solution {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        int len = word.length();

        auto canPlace = [&](int r, int c, int dr, int dc) {
            for (int i = 0; i < len; ++i) {
                int nr = r + i * dr;
                int nc = c + i * dc;
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) return false;
                if (board[nr][nc] != ' ' && board[nr][nc] != word[i]) return false;
            }
            int beforeR = r - dr;
            int beforeC = c - dc;
            int afterR = r + len * dr;
            int afterC = c + len * dc;
            if ((beforeR >= 0 && beforeR < m && beforeC >= 0 && beforeC < n && board[beforeR][beforeC] != '#') ||
                (afterR >= 0 && afterR < m && afterC >= 0 && afterC < n && board[afterR][afterC] != '#')) {
                return false;
            }
            return true;
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (canPlace(i, j, 0, 1) || canPlace(i, j, 1, 0) ||
                    canPlace(i, j, 0, -1) || canPlace(i, j, -1, 0)) {
                    return true;
                }
            }
        }
        return false;           
    }
};
