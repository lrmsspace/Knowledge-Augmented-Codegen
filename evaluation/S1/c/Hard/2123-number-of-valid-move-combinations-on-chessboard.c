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
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countCombinations(char** pieces, int piecesSize, int** positions, int positionsSize, int* positionsColSize) {
    // Directions for each piece type
    int rookDirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int bishopDirs[4][2] = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    int queenDirs[8][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};

    // Function to get valid moves for a piece
    void getValidMoves(char* piece, int* pos, int moves[][2], int* moveCount) {
        int (*dirs)[2];
        int dirCount;
        if (strcmp(piece, "rook") == 0) {
            dirs = rookDirs; dirCount = 4;
        } else if (strcmp(piece, "bishop") == 0) {
            dirs = bishopDirs; dirCount = 4;
        } else { // queen
            dirs = queenDirs; dirCount = 8;
        }

        *moveCount = 0;
        for (int d = 0; d < dirCount; d++) {
            for (int step = 1; step < 8; step++) {
                int newRow = pos[0] + dirs[d][0] * step;
                int newCol = pos[1] + dirs[d][1] * step;
                if (newRow < 1 || newRow > 8 || newCol < 1 || newCol > 8) break;
                moves[(*moveCount)++][0] = newRow;
                moves[(*moveCount)++][1] = newCol;
            }
        }
        // Include staying in place
        moves[(*moveCount)++][0] = pos[0];
        moves[(*moveCount)++][1] = pos[1];
    }

    // Backtracking to count valid combinations
    int totalCombinations = 0;
    void backtrack(int index, int positions[][2], int pieceMoves[][64][2], int moveCounts[], int* currentPositions) {
        if (index == piecesSize) {
            // Check for collisions
            int occupied[9][9] = {0};
            for (int i = 0; i < piecesSize; i++) {
                int r = currentPositions[i * 2];
                int c = currentPositions[i * 2 + 1];
                if (occupied[r][c]) return; // Collision detected
                occupied[r][c] = 1;
            }
            totalCombinations++;
            return;
        }
        for (int m = 0; m < moveCounts[index]; m++) {
            currentPositions[index * 2] = pieceMoves[index][m][0];
            currentPositions[index * 2 + 1] = pieceMoves[index][m][1];
            backtrack(index + 1, positions, pieceMoves, moveCounts, currentPositions);
        }

}
    int pieceMoves[4][64][2]; // Max 4 pieces, each with up to 64 moves
    int moveCounts[4];
    for (int i = 0; i < piecesSize; i++) {
        getValidMoves(pieces[i], positions[i], pieceMoves[i], &moveCounts[i]);
    }
    int currentPositions[8]; // Max 4 pieces, each with row and col
    backtrack(0, positions, pieceMoves, moveCounts, currentPositions);
    return totalCombinations;
}
