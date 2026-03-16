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

class Solution {
    public int[] kWeakestRows(int[][] mat, int k) {
        int m = mat.length;
        int n = mat[0].length;
        int[] soldiersCount = new int[m];
        
        // Count soldiers in each row
        for (int i = 0; i < m; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    count++;
                } else {
                    break; // Since soldiers are always before civilians
                }
            }
            soldiersCount[i] = count;
        }
        
        // Create an array of row indices
        Integer[] rowIndices = new Integer[m];
        for (int i = 0; i < m; i++) {
            rowIndices[i] = i;
        }
        
        // Sort the row indices based on the number of soldiers and then by index
        Arrays.sort(rowIndices, (a, b) -> {
            if (soldiersCount[a] != soldiersCount[b]) {
                return Integer.compare(soldiersCount[a], soldiersCount[b]);
            } else {
                return Integer.compare(a, b);
            }
        });
        
        // Prepare the result array with the first k weakest rows
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = rowIndices[i];
        }
        
        return result;          
    }
}
