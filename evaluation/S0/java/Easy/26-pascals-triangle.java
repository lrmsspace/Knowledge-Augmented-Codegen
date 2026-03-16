// Source: https://leetcode.com/problems/pascals-triangle/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer numRows, return the first numRows of Pascal's triangle.
//
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
//
// Example:
// Input: numRows = 5
// Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
//
// Constraints:
// 1 <= numRows <= 30
//

class Solution {
    public List<List<Integer>> generate(int numRows) {
        List<List<Integer>> triangle = new ArrayList<>();

        for (int rowNum = 0; rowNum < numRows; rowNum++) {
            List<Integer> row = new ArrayList<>();
            for (int j = 0; j <= rowNum; j++) {
                if (j == 0 || j == rowNum) {
                    row.add(1);
                } else {
                    int val = triangle.get(rowNum - 1).get(j - 1) + triangle.get(rowNum - 1).get(j);
                    row.add(val);
                }
            }
            triangle.add(row);
        }

        return triangle;            
    }
}
