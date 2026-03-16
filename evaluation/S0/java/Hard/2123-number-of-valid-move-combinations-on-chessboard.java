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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countCombinations(String[] pieces, int[][] positions) {
        int n = pieces.length;
        int[][] directions = new int[n][];
        for (int i = 0; i < n; i++) {
            directions[i] = getDirections(pieces[i]);
        }
        return backtrack(positions, directions, 0);         
    }
}
