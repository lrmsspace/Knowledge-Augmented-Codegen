// Source: https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/   |   Difficulty: Hard
//
// Problem Description:
// Nearly everyone has used the Multiplication Table. The multiplication table of size m x n is an integer matrix mat where mat[i][j] == i * j (1-indexed).
//
// Given three integers m, n, and k, return the kth smallest element in the m x n multiplication table.
//
// Example:
// Input: m = 3, n = 3, k = 5
// Output: 3
// Explanation: The 5th smallest number is 3.
//
// Constraints:
// 1 <= m, n <= 3 * 104
// 	1 <= k <= m * n
//

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int left = 1, right = m * n;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            int count = 0;
            
            for (int i = 1; i <= m; i++) {
                count += std::min(mid / i, n);
            }
            
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;            
    }
};
