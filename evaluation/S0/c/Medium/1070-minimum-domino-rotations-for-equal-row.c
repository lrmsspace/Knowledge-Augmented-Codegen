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

int minDominoRotations(int* tops, int topsSize, int* bottoms, int bottomsSize) {
    int countTop[7] = {0};
    int countBottom[7] = {0};
    int countSame[7] = {0};
    
    for (int i = 0; i < topsSize; i++) {
        countTop[tops[i]]++;
        countBottom[bottoms[i]]++;
        if (tops[i] == bottoms[i]) {
            countSame[tops[i]]++;
        }
    }
    
    int minRotations = topsSize + 1;
    
    for (int num = 1; num <= 6; num++) {
        if (countTop[num] + countBottom[num] - countSame[num] == topsSize) {
            int rotations = topsSize - (countTop[num] > countBottom[num] ? countTop[num] : countBottom[num]);
            if (rotations < minRotations) {
                minRotations = rotations;
            }
        }
    }
    
    return (minRotations == topsSize + 1) ? -1 : minRotations;      
}
