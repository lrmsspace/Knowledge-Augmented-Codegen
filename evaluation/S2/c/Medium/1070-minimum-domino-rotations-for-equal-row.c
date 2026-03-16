// Source: https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/   |   Difficulty: Medium
//
// Problem Description:
// In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
//
// We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
//
// Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.
//
// If it cannot be done, return -1.
//
// Example:
// Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
// Output: 2
// Explanation: 
// The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
// If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
//
// Constraints:
// 2 <= tops.length <= 2 * 104
// 	bottoms.length == tops.length
// 	1 <= tops[i], bottoms[i] <= 6
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

int minDominoRotations(int* tops, int topsSize, int* bottoms, int bottomsSize) {
    int count[7][2] = {0}; // count[number][0] for tops, count[number][1] for bottoms
    for (int i = 0; i < topsSize; i++) {
        count[tops[i]][0]++;
        count[bottoms[i]][1]++;
    }
    
    for (int num = 1; num <= 6; num++) {
        if (count[num][0] + count[num][1] >= topsSize) {
            // We can make all tops or all bottoms equal to num
            int rotations = topsSize - (count[num][0] > count[num][1] ? count[num][0] : count[num][1]);
            return rotations;
        }
    }
    
    return -1; // Not possible to make all tops or bottoms the same     
}
