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

bool placeWordInCrossword(char** board, int boardSize, int* boardColSize, char* word) {
    int wordLen = strlen(word);
    int rows = boardSize;
    int cols = boardColSize[0];

    // Helper function to check if the word can be placed starting from (r, c) in direction (dr, dc)
    bool canPlace(int r, int c, int dr, int dc) {
        for (int i = 0; i < wordLen; i++) {
            int nr = r + i * dr;
            int nc = c + i * dc;
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || board[nr][nc] == '#') {
                return false;
            }
            if (board[nr][nc] != ' ' && board[nr][nc] != word[i]) {
                return false;
            }
        }
        // Check boundaries
        int beforeR = r - dr;
        int beforeC = c - dc;
        int afterR = r + wordLen * dr;
        int afterC = c + wordLen * dc;

        if ((beforeR >= 0 && beforeR < rows && beforeC >= 0 && beforeC < cols && board[beforeR][beforeC] != '#') ||
            (afterR >= 0 && afterR < rows && afterC >= 0 && afterC < cols && board[afterR][afterC] != '#')) {
            return false;
        }
        return true;
    }

    // Check all possible placements
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (canPlace(r, c, 0, 1) || canPlace(r, c, 1, 0) || // left to right or top to bottom
                canPlace(r, c, 0, -1) || canPlace(r, c, -1, 0)) { // right to left or bottom to top
                return true;
            }
        }
    }
    return false;       
}
