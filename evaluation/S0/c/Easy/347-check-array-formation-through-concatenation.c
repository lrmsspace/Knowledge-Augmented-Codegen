// Source: https://leetcode.com/problems/check-array-formation-through-concatenation/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of distinct integers arr and an array of integer arrays pieces, where the integers in pieces are distinct. Your goal is to form arr by concatenating the arrays in pieces in any order. However, you are not allowed to reorder the integers in each array pieces[i].
//
// Return true if it is possible to form the array arr from pieces. Otherwise, return false.
//
// Example:
// Input: arr = [15,88], pieces = [[88],[15]]
// Output: true
// Explanation: Concatenate [15] then [88]
//
// Constraints:
// 1 <= pieces.length <= arr.length <= 100
// 	sum(pieces[i].length) == arr.length
// 	1 <= pieces[i].length <= arr.length
// 	1 <= arr[i], pieces[i][j] <= 100
// 	The integers in arr are distinct.
// 	The integers in pieces are distinct (i.e., If we flatten pieces in a 1D array, all the integers in this array are distinct).
//

bool canFormArray(int* arr, int arrSize, int** pieces, int piecesSize, int* piecesColSize) {
    int map[101];
    for (int i = 0; i <= 100; i++) {
        map[i] = -1;
    }
    for (int i = 0; i < piecesSize; i++) {
        map[pieces[i][0]] = i;
    }

    int i = 0;
    while (i < arrSize) {
        int pieceIndex = map[arr[i]];
        if (pieceIndex == -1) {
            return false;
        }
        for (int j = 0; j < piecesColSize[pieceIndex]; j++) {
            if (arr[i] != pieces[pieceIndex][j]) {
                return false;
            }
            i++;
        }
    }
    return true;        
}
