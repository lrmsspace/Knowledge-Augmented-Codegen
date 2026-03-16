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
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;

        for (int row = 0; row < numRows; ++row) {
            triangle.push_back(vector<int>(row + 1, 1));

            for (int col = 1; col < row; ++col) {
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
        }

        return triangle;            
    }
};
