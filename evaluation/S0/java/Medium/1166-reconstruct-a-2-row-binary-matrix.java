// Source: https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given the following details of a matrix with n columns and 2 rows :
//
//
// 	The matrix is a binary matrix, which means each element in the matrix can be 0 or 1.
// 	The sum of elements of the 0-th(upper) row is given as upper.
// 	The sum of elements of the 1-st(lower) row is given as lower.
// 	The sum of elements in the i-th column(0-indexed) is colsum[i], where colsum is given as an integer array with length n.
//
//
// Your task is to reconstruct the matrix with upper, lower and colsum.
//
// Return it as a 2-D integer array.
//
// If there are more than one valid solution, any of them will be accepted.
//
// If no valid solution exists, return an empty 2-D array.
//
// Example:
// Input: upper = 2, lower = 1, colsum = [1,1,1]
// Output: [[1,1,0],[0,0,1]]
// Explanation: [[1,0,1],[0,1,0]], and [[0,1,1],[1,0,0]] are also correct answers.
//
// Constraints:
// 1 <= colsum.length <= 10^5
// 	0 <= upper, lower <= colsum.length
// 	0 <= colsum[i] <= 2
//

class Solution {
    public List<List<Integer>> reconstructMatrix(int upper, int lower, int[] colsum) {
        int n = colsum.length;
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> upperRow = new ArrayList<>(Collections.nCopies(n, 0));
        List<Integer> lowerRow = new ArrayList<>(Collections.nCopies(n, 0));

        for (int i = 0; i < n; i++) {
            if (colsum[i] == 2) {
                upperRow.set(i, 1);
                lowerRow.set(i, 1);
                upper--;
                lower--;
            }
        }

        for (int i = 0; i < n; i++) {
            if (colsum[i] == 1) {
                if (upper > 0) {
                    upperRow.set(i, 1);
                    upper--;
                } else if (lower > 0) {
                    lowerRow.set(i, 1);
                    lower--;
                } else {
                    return new ArrayList<>(); // No valid solution
                }
            }
        }

        if (upper == 0 && lower == 0) {
            result.add(upperRow);
            result.add(lowerRow);
            return result;
        } else {
            return new ArrayList<>(); // No valid solution
        }           
    }
}
