// Source: https://leetcode.com/problems/spiral-matrix-iv/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers m and n, which represent the dimensions of a matrix.
//
// You are also given the head of a linked list of integers.
//
// Generate an m x n matrix that contains the integers in the linked list presented in spiral order (clockwise), starting from the top-left of the matrix. If there are remaining empty spaces, fill them with -1.
//
// Return the generated matrix.
//
// Example:
// Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
// Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
// Explanation: The diagram above shows how the values are printed in the matrix.
// Note that the remaining spaces in the matrix are filled with -1.
//
// Constraints:
// 1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	The number of nodes in the list is in the range [1, m * n].
// 	0 <= Node.val <= 1000
//
// Helpful references (internal KB):
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Gauss method for solving system of linea (matrix, number, simulation)
//   • When to use: Use to solve systems of linear equations, determine matrix rank, or find matrix inverses. It helps analyze if a system has unique, infinite, or no solutions.
//   • Idea: Gaussian elimination transforms an augmented matrix into row echelon form using elementary row operations to solve linear systems. Gauss-Jordan extends this to reduced row echelon form for direct solutions, typically with O(N^3) complexity.
//   • Invariants: The solution set of the system of equations remains unchanged after each elementary row operation.; After processing column k, all elements below the pivot in that column are zero.
//   • Tips: Use partial pivoting to improve numerical stability and avoid division by zero.; Handle floating-point precision issues carefully, using a small epsilon for comparisons.
//   • Pitfalls: Encountering division by zero if a pivot element is zero and no pivoting is applied.; Numerical instability and accumulation of floating-point errors, especially without pivoting.
// - Gauss method for solving system of linea (matrix, number, simulation)
//   • When to use: Use when solving systems of linear equations, including those over finite fields (modulo p), to find unique, multiple, or no solutions.
//   • Idea: Gauss-Jordan elimination systematically transforms a system of linear equations into an equivalent, simpler form (row echelon or reduced row echelon) using elementary row operations to find solutions. This process typically has a time complexity of O(N^2 * M) for an N x M matrix.
//   • Invariants: After k steps, the first k columns form an identity submatrix (or a column with 1 at pivot and 0s elsewhere) in the upper-left kxk block.; The system of equations represented by the augmented matrix remains equivalent to the original system.
//   • Tips: Always perform row operations on the augmented matrix (A|b) to ensure consistency.; Choose a pivot with the largest absolute value to improve numerical stability and reduce error propagation.
//   • Pitfalls: Division by zero if a pivot element is zero and no suitable row swap is found.; Numerical instability with floating-point numbers if pivots are very small, leading to precision issues.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> matrix(m, vector<int>(n, -1));
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        while (head) {
            for (int i = left; i <= right && head; ++i) {
                matrix[top][i] = head->val;
                head = head->next;
            }
            ++top;
            for (int i = top; i <= bottom && head; ++i) {
                matrix[i][right] = head->val;
                head = head->next;
            }
            --right;
            for (int i = right; i >= left && head; --i) {
                matrix[bottom][i] = head->val;
                head = head->next;
            }
            --bottom;
            for (int i = bottom; i >= top && head; --i) {
                matrix[i][left] = head->val;
                head = head->next;
            }
            ++left;
        }
        return matrix;          
    }
};
