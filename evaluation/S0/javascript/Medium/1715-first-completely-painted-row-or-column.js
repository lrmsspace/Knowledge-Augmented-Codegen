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

/**
 * @param {number[]} arr
 * @param {number[][]} mat
 * @return {number}
 */
var firstCompleteIndex = function(arr, mat) {
    const m = mat.length;
    const n = mat[0].length;
    const positionMap = new Map();
    const rowCount = new Array(m).fill(0);
    const colCount = new Array(n).fill(0);
        
    for (let r = 0; r < m; r++) {
        for (let c = 0; c < n; c++) {
            positionMap.set(mat[r][c], [r, c]);
        }
    }

    for (let i = 0; i < arr.length; i++) {
        const [r, c] = positionMap.get(arr[i]);
        rowCount[r]++;
        colCount[c]++;
        if (rowCount[r] === n || colCount[c] === m) {
            return i;
        }
    }
    return -1;  
            
};
