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
// Helpful references (internal KB):
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool placeWordInCrossword(char** board, int boardSize, int* boardColSize, char* word) {
    int rows = boardSize;
    int cols = boardColSize[0];
    int wordLen = 0;
    while (word[wordLen] != '\0') {
        wordLen++;
    }

    // Helper function to check if the word can fit in a given segment
    bool canPlace(char* segment, int length) {
        if (length != wordLen) return false;
        for (int i = 0; i < length; i++) {
            if (segment[i] != ' ' && segment[i] != word[i]) {
                return false;
            }
        }
        return true;
    }

    // Check rows
    for (int r = 0; r < rows; r++) {
        int c = 0;
        while (c < cols) {
            if (board[r][c] == '#') {
                c++;
                continue;
            }
            int start = c;
            while (c < cols && board[r][c] != '#') {
                c++;
            }
            int length = c - start;
            char* segment = (char*)malloc((length + 1) * sizeof(char));
            for (int i = 0; i < length; i++) {
                segment[i] = board[r][start + i];
            }
            segment[length] = '\0';
            if (canPlace(segment, length)) {
                free(segment);
                return true;
            }
            // Check reversed
            for (int i = 0; i < length / 2; i++) {
                char temp = segment[i];
                segment[i] = segment[length - 1 - i];
                segment[length - 1 - i] = temp;
            }
            if (canPlace(segment, length)) {
                free(segment);
                return true;
            }
            free(segment);
        }
    }

    // Check columns
    for (int c = 0; c < cols; c++) {
        int r = 0;
        while (r < rows) {
            if (board[r][c] == '#') {
                r++;
                continue;
            }
            int start = r;
            while (r < rows && board[r][c] != '#') {
                r++;
            }
            int length = r - start;
            char* segment = (char*)malloc((length + 1) * sizeof(char));
            for (int i = 0; i < length; i++) {
                segment[i] = board[start + i][c];
            }
            segment[length] = '\0';
            if (canPlace(segment, length)) {
                free(segment);
                return true;
            }
            // Check reversed
            for (int i = 0; i < length / 2; i++) {
                char temp = segment[i];
                segment[i] = segment[length - 1 - i];
                segment[length - 1 - i] = temp;
            }
            if (canPlace(segment, length)) {
                free(segment);
                return true;
            }
            free(segment);
        }
    }
    return false;
}
