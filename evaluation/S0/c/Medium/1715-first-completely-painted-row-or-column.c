// Source: https://leetcode.com/problems/first-completely-painted-row-or-column/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both contain all the integers in the range [1, m * n].
//
// Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].
//
// Return the smallest index i at which either a row or a column will be completely painted in mat.
//
// Example:
// Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
// Output: 2
// Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
//
// Constraints:
// m == mat.length
// 	n = mat[i].length
// 	arr.length == m * n
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= arr[i], mat[r][c] <= m * n
// 	All the integers of arr are unique.
// 	All the integers of mat are unique.
//

int firstCompleteIndex(int* arr, int arrSize, int** mat, int matSize, int* matColSize) {
    int m = matSize;
    int n = matColSize[0];
    
    int pos[m * n + 1][2];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            pos[mat[i][j]][0] = i;
            pos[mat[i][j]][1] = j;
        }
    }
    
    int rowCount[m];
    int colCount[n];
    for (int i = 0; i < m; i++) {
        rowCount[i] = 0;
    }
    for (int j = 0; j < n; j++) {
        colCount[j] = 0;
    }
    
    for (int i = 0; i < arrSize; i++) {
        int val = arr[i];
        int r = pos[val][0];
        int c = pos[val][1];
        
        rowCount[r]++;
        colCount[c]++;
        
        if (rowCount[r] == n || colCount[c] == m) {
            return i;
        }
    }
    
    return -1; // This line should never be reached given the problem constraints.      
}
