// Source: https://leetcode.com/problems/kth-smallest-instructions/   |   Difficulty: Hard
//
// Problem Description:
// Bob is standing at cell (0, 0), and he wants to reach destination: (row, column). He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.
//
// The instructions are represented as a string, where each character is either:
//
//
// 	'H', meaning move horizontally (go right), or
// 	'V', meaning move vertically (go down).
//
//
// Multiple instructions will lead Bob to destination. For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.
//
// However, Bob is very picky. Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.
//
// Given an integer array destination and an integer k, return the kth lexicographically smallest instructions that will take Bob to destination.
//
// Example:
// Input: destination = [2,3], k = 1
// Output: "HHHVV"
// Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
// ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].
//
// Constraints:
// destination.length == 2
// 	1 <= row, column <= 15
// 	1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b​​​​​.
//

class Solution {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
        int row = destination[0], col = destination[1];
        // Precompute binomial coefficients
        vector<vector<long long>> comb(row + col + 1, vector<long long>(col + 1, 0));
        for (int i = 0; i <= row + col; i++) {
            comb[i][0] = 1;
            for (int j = 1; j <= min(i, col); j++) {
                comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            }
        }
        
        string result;
        while (row > 0 && col > 0) {
            long long countHFirst = comb[row + col - 1][col - 1];
            if (k <= countHFirst) {
                result += 'H';
                col--;
            } else {
                result += 'V';
                k -= countHFirst;
                row--;
            }
        }
        
        // Append remaining H's or V's
        result += string(col, 'H');
        result += string(row, 'V');
        
        return result;          
    }
};
