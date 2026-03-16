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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.



char * alphabetBoardPath(char * target){
    int pos[26][2];
    char board[6][6] = {"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"};
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5 && board[i][j]; ++j) {
            pos[board[i][j] - 'a'][0] = i;
            pos[board[i][j] - 'a'][1] = j;
        }
    }

    char *result = malloc(300);
    int idx = 0, x = 0, y = 0;
    for (int i = 0; target[i]; ++i) {
        int target_x = pos[target[i] - 'a'][0];
        int target_y = pos[target[i] - 'a'][1];

        while (x > target_x) {
            result[idx++] = 'U';
            x--;
        }
        while (y > target_y) {
            result[idx++] = 'L';
            y--;
        }
        while (x < target_x) {
            result[idx++] = 'D';
            x++;
        }
        while (y < target_y) {
            result[idx++] = 'R';
            y++;
        }
        result[idx++] = '!';
    }
    result[idx] = '\0';
    return result;
}
