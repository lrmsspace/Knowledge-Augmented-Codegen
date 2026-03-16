// Source: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-ii/   |   Difficulty: Hard
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
// 3 <= m == board.length <= 500
// 	3 <= n == board[i].length <= 500
// 	-109 <= board[i][j] <= 109
//

class Solution {
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        long long result = LLONG_MIN;
        
        for (int c1 = 0; c1 < n; c1++) {
            for (int c2 = 0; c2 < n; c2++) {
                if (c2 == c1) continue;
                
                // Prepare row sums excluding columns c1 and c2
                vector<long long> rowSums(m, 0);
                for (int r = 0; r < m; r++) {
                    rowSums[r] = board[r][c1] + board[r][c2];
                }
                
                // Find top 3 rows with maximum sums
                priority_queue<long long> pq;
                for (int r = 0; r < m; r++) {
                    pq.push(rowSums[r]);
                }
                
                long long currentSum = 0;
                for (int k = 0; k < 3; k++) {
                    if (!pq.empty()) {
                        currentSum += pq.top();
                        pq.pop();
                    }
                }
                
                result = max(result, currentSum);
            }
        }
        
        return result;          
    }
};
