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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countCombinations(char** pieces, int piecesSize, int** positions, int positionsSize, int* positionsColSize) {
    const int MOD = 1000000007;
    int directions[3][8][2] = {
        {{1,0},{-1,0},{0,1},{0,-1}}, // Rook
        {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}}, // Queen
        {{1,1},{1,-1},{-1,1},{-1,-1}} // Bishop
    };
    int maxMoves[3] = {7, 7, 7}; // Max moves for Rook, Queen, Bishop

    // Generate all possible states for each piece
    int totalStates = 1;
    for (int i = 0; i < piecesSize; i++) {
        int pieceType = (strcmp(pieces[i], "rook") == 0) ? 0 : (strcmp(pieces[i], "queen") == 0) ? 1 : 2;
        int moveOptions = 0;
        for (int d = 0; d < (pieceType == 0 ? 4 : pieceType == 1 ? 8 : 4); d++) {
            moveOptions += maxMoves[pieceType];
        }
        totalStates *= (moveOptions + 1); // +1 for staying in place
    }

    int (*validStates)[piecesSize] = malloc(totalStates * sizeof(*validStates));
    int validCount = 0;

    for (int state = 0; state < totalStates; state++) {
        int tempState = state;
        int currentPositions[piecesSize][2];
        for (int i = 0; i < piecesSize; i++) {
            currentPositions[i][0] = positions[i][0];
            currentPositions[i][1] = positions[i][1];
        }

        int isValid = 1;
        for (int i = 0; i < piecesSize; i++) {
            int pieceType = (strcmp(pieces[i], "rook") == 0) ? 0 : (strcmp(pieces[i], "queen") == 0) ? 1 : 2;
            int moveIndex = tempState % (maxMoves[pieceType] * ((pieceType == 0) ? 4 : (pieceType == 1)
                ? 8 : 4) + 1);
            tempState /= (maxMoves[pieceType] * ((pieceType == 0) ? 4 : (pieceType == 1) ? 8 : 4) + 1);
            if (moveIndex > 0) {
                int dirIndex = (moveIndex - 1) / maxMoves[pieceType];
                int steps = (moveIndex - 1) % maxMoves[pieceType] + 1;
                currentPositions[i][0] += directions[pieceType][dirIndex][0] * steps;
                currentPositions[i][1] += directions[pieceType][dirIndex][1] * steps;
            }
            // Check bounds
            if (currentPositions[i][0] < 1 || currentPositions[i][0] > 8 || currentPositions[i][1] < 1 || currentPositions[i][1] > 8) {
                isValid = 0;
                break;
            }
        }
        // Check for collisions
        if (isValid) {
            for (int i = 0; i < piecesSize; i++) {
                for (int j = i + 1; j < piecesSize; j++) {
                    if (currentPositions[i][0] == currentPositions[j][0] && currentPositions[i][1] == currentPositions[j][1]) {
                        isValid = 0;
                        break;
                    }
                }
                if (!isValid) break;
            }
        }
        if (isValid) {
            for (int i = 0; i < piecesSize; i++) {
                validStates[validCount][i] = currentPositions[i][0] * 10 + currentPositions[i][1];
            }
            validCount++;
        }
    }
    // Dynamic Programming to count valid combinations
    long* dpPrev = (long*)calloc(validCount, sizeof(long));
    long* dpCurr = (long*)calloc(validCount, sizeof(long));
    for (int i = 0; i < validCount; i++) {
        dpPrev[i] = 1;
    }
    for (int step = 1; step <= 7; step++) {
        for (int i = 0; i < validCount; i++) {
            dpCurr[i] = 0;
            for (int j = 0; j < validCount; j++) {
                int collision = 0;
                for (int p = 0; p < piecesSize; p++) {
                    if (validStates[i][p] == validStates[j][p]) {
                        collision = 1;
                        break;
                    }
                }
                if (!collision) {
                    dpCurr[i] = (dpCurr[i] + dpPrev[j]) % MOD;
                }
            }
        }
        long* temp = dpPrev;
        dpPrev = dpCurr;
        dpCurr = temp;
    }
    long result = 0;
    for (int i = 0; i < validCount; i++) {    
        result = (result + dpPrev[i]) % MOD;
    }
    free(validStates);
    free(dpPrev);
    free(dpCurr);
    return (int)result;
}
