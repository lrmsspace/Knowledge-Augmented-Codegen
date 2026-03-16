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
    public boolean placeWordInCrossword(char[][] board, String word) {
        int rows = board.length;
        int cols = board[0].length;
        String reversedWord = new StringBuilder(word).reverse().toString();

        // Check rows
        for (int r = 0; r < rows; r++) {
            String rowStr = new String(board[r]);
            if (canPlaceWord(rowStr, word) || canPlaceWord(rowStr, reversedWord)) {
                return true;
            }
        }

        // Check columns
        for (int c = 0; c < cols; c++) {
            StringBuilder colStrBuilder = new StringBuilder();
            for (int r = 0; r < rows; r++) {
                colStrBuilder.append(board[r][c]);
            }
            String colStr = colStrBuilder.toString();
            if (canPlaceWord(colStr, word) || canPlaceWord(colStr, reversedWord)) {
                return true;
            }
        }

        return false;           
    }
}
