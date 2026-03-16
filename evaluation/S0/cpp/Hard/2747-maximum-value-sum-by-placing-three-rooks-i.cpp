// Source: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given a m x n 2D array board representing a chessboard, where board[i][j] represents the value of the cell (i, j).
//
// Rooks in the same row or column attack each other. You need to place three rooks on the chessboard such that the rooks do not attack each other.
//
// Return the maximum sum of the cell values on which the rooks are placed.
//
// Example:
// Input: board = [[-3,1,1,1],[-3,1,-3,1],[-3,2,1,1]]
//
// Output: 4
//
// Explanation:
//
//
//
// We can place the rooks in the cells (0, 2), (1, 3), and (2, 1) for a sum of 1 + 1 + 2 = 4.
//
// Constraints:
// 3 <= m == board.length <= 100
// 	3 <= n == board[i].length <= 100
// 	-109 <= board[i][j] <= 109
//

class Solution {
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        long long maxSum = LLONG_MIN;
        
        for (int r1 = 0; r1 < m; r1++) {
            for (int r2 = 0; r2 < m; r2++) {
                if (r2 == r1) continue;
                for (int r3 = 0; r3 < m; r3++) {
                    if (r3 == r1 || r3 == r2) continue;
                    
                    // Collect values from rows r1, r2, r3
                    vector<int> vals;
                    for (int c = 0; c < n; c++) {
                        vals.push_back(board[r1][c]);
                        vals.push_back(board[r2][c]);
                        vals.push_back(board[r3][c]);
                    }
                    
                    // Sort and pick top 3 values
                    sort(vals.rbegin(), vals.rend());
                    long long currentSum = (long long)vals[0] + vals[1] + vals[2];
                    maxSum = max(maxSum, currentSum);
                }
            }
        }
        
        return maxSum;          
    }
};
