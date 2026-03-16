// Source: https://leetcode.com/problems/largest-submatrix-with-rearrangements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
//
// Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.
//
// Example:
// Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m * n <= 105
// 	matrix[i][j] is either 0 or 1.
//

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> height(m, vector<int>(n, 0));

        // Compute heights of consecutive 1s for each column
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                if (matrix[i][j] == 1) {
                    height[i][j] = (i == 0 ? 1 : height[i - 1][j] + 1);
                }
            }
        }

        int maxArea = 0;

        // For each row, sort heights and calculate max area
        for (int i = 0; i < m; ++i) {
            vector<int> sortedHeights = height[i];
            sort(sortedHeights.begin(), sortedHeights.end(), greater<int>());

            for (int j = 0; j < n; ++j) {
                int area = sortedHeights[j] * (j + 1);
                maxArea = max(maxArea, area);
            }
        }

        return maxArea;         
    }
};
