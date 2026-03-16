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
// Notes:
//
//
// 	No two pieces will start in the same square.
// 	You may choose the square a piece is already on as its destination.
// 	If two pieces are directly adjacent to each other, it is valid for them to move past each other and swap positions in one second.
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
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countCombinations(String[] pieces, int[][] positions) {
         // The number of pieces is small (n <= 4), so we can use enumeration to check all possible move combinations.
        // For each piece, we will calculate the possible destination squares it can move to based on its type and current position.
        // Then, we will generate all combinations of these destination squares (one for each piece) and check if any two pieces occupy the same square at any time during their movement.
        // We can simulate the movement of the pieces for each combination and count how many combinations are valid (no collisions).
        
        // Step 1: Calculate possible moves for each piece
        List<List<int[]>> possibleMoves = new ArrayList<>();
        for (int i = 0; i < pieces.length; i++) {
            String type = pieces[i];
            int r = positions[i][0];
            int c = positions[i][1];
            List<int[]> movesForPiece = calculatePossibleMoves(type, r, c);
            possibleMoves.add(movesForPiece);
        }
        
        // Step 2: Generate all combinations of moves and check for validity
        return countValidCombinations(possibleMoves);

    }
}
