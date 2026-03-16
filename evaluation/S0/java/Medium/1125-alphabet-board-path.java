// Source: https://leetcode.com/problems/alphabet-board-path/   |   Difficulty: Medium
//
// Problem Description:
// On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].
//
// Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.
//
//
//
// We may make the following moves:
//
//
// 	'U' moves our position up one row, if the position exists on the board;
// 	'D' moves our position down one row, if the position exists on the board;
// 	'L' moves our position left one column, if the position exists on the board;
// 	'R' moves our position right one column, if the position exists on the board;
// 	'!' adds the character board[r][c] at our current position (r, c) to the answer.
//
//
// (Here, the only positions that exist on the board are positions with letters on them.)
//
// Return a sequence of moves that makes our answer equal to target in the minimum number of moves.  You may return any path that does so.
//
// Example:
// Input: target = "leet"
// Output: "DDR!UURRR!!DDD!"
//
// Constraints:
// 1 <= target.length <= 100
// 	target consists only of English lowercase letters.
//

class Solution {
    public String alphabetBoardPath(String target) {
        StringBuilder result = new StringBuilder();
        int currentRow = 0;
        int currentCol = 0;

        for (char ch : target.toCharArray()) {
            int targetIndex = ch - 'a';
            int targetRow = targetIndex / 5;
            int targetCol = targetIndex % 5;

            // Special case for 'z' to avoid invalid moves
            if (ch == 'z') {
                // Move left first if needed
                while (currentCol > targetCol) {
                    result.append('L');
                    currentCol--;
                }
                // Move down to 'z'
                while (currentRow < targetRow) {
                    result.append('D');
                    currentRow++;
                }
            } else {
                // Move up first if needed
                while (currentRow > targetRow) {
                    result.append('U');
                    currentRow--;
                }
                // Move left if needed
                while (currentCol > targetCol) {
                    result.append('L');
                    currentCol--;
                }
                // Move down if needed
                while (currentRow < targetRow) {
                    result.append('D');
                    currentRow++;
                }
                // Move right if needed
                while (currentCol < targetCol) {
                    result.append('R');
                    currentCol++;
                }
            }

            // Append '!' to select the character
            result.append('!');
        }

        return result.toString();           
    }
}
