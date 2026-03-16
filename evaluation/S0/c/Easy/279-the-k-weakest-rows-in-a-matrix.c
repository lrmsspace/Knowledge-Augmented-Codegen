// Source: https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians). The soldiers are positioned in front of the civilians. That is, all the 1's will appear to the left of all the 0's in each row.
//
// A row i is weaker than a row j if one of the following is true:
//
//
// 	The number of soldiers in row i is less than the number of soldiers in row j.
// 	Both rows have the same number of soldiers and i < j.
//
//
// Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.
//
// Example:
// Input: mat = 
// [[1,1,0,0,0],
//  [1,1,1,1,0],
//  [1,0,0,0,0],
//  [1,1,0,0,0],
//  [1,1,1,1,1]], 
// k = 3
// Output: [2,0,3]
// Explanation: 
// The number of soldiers in each row is: 
// - Row 0: 2 
// - Row 1: 4 
// - Row 2: 1 
// - Row 3: 2 
// - Row 4: 5 
// The rows ordered from weakest to strongest are [2,0,3,1,4].
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	2 <= n, m <= 100
// 	1 <= k <= m
// 	matrix[i][j] is either 0 or 1.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize) {
    int* result = (int*)malloc(k * sizeof(int));
    int count[matSize];
    for (int i = 0; i < matSize; i++) {
        int soldierCount = 0;
        for (int j = 0; j < *matColSize; j++) {
            if (mat[i][j] == 1) {
                soldierCount++;
            } else {
                break; // Since soldiers are always before civilians
            }
        }
        count[i] = soldierCount;
    }

    for (int i = 0; i < k; i++) {
        int minIndex = -1;
        for (int j = 0; j < matSize; j++) {
            if (count[j] != -1 && (minIndex == -1 || count[j] < count[minIndex])) {
                minIndex = j;
            }
        }
        result[i] = minIndex;
        count[minIndex] = -1; // Mark this row as used
    }

    *returnSize = k;
    return result;      
}
