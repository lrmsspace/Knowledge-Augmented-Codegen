# Source: https://leetcode.com/problems/decode-the-slanted-ciphertext/   |   Difficulty: Medium
#
# Problem Description:
# A string originalText is encoded using a slanted transposition cipher to a string encodedText with the help of a matrix having a fixed number of rows rows.
#
# originalText is placed first in a top-left to bottom-right manner.
#
# The blue cells are filled first, followed by the red cells, then the yellow cells, and so on, until we reach the end of originalText. The arrow indicates the order in which the cells are filled. All empty cells are filled with ' '. The number of columns is chosen such that the rightmost column will not be empty after filling in originalText.
#
# encodedText is then formed by appending all characters of the matrix in a row-wise fashion.
#
# The characters in the blue cells are appended first to encodedText, then the red cells, and so on, and finally the yellow cells. The arrow indicates the order in which the cells are accessed.
#
# For example, if originalText = "cipher" and rows = 3, then we encode it in the following manner:
#
# The blue arrows depict how originalText is placed in the matrix, and the red arrows denote the order in which encodedText is formed. In the above example, encodedText = "ch ie pr".
#
# Given the encoded string encodedText and number of rows rows, return the original string originalText.
#
# Note: originalText does not have any trailing spaces ' '. The test cases are generated such that there is only one possible originalText.
#
# Example:
# Input: encodedText = "ch   ie   pr", rows = 3
# Output: "cipher"
# Explanation: This is the same example described in the problem description.
#
# Constraints:
# 0 <= encodedText.length <= 106
# 	encodedText consists of lowercase English letters and ' ' only.
# 	encodedText is a valid encoding of some originalText that does not have trailing spaces.
# 	1 <= rows <= 1000
# 	The testcases are generated such that there is only one possible originalText.
#
# Helpful references (internal KB):
# - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
#   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
#   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
#   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
#   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
#   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
# - Finding the rank of a matrix (matrix, simulation, enumeration)
#   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
#   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
#   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
#   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
#   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
# - Calculating the determinant of a matrix by Gauss (matrix, number, simulation, counting)
#   • When to use: When needing to compute the determinant of a square matrix, especially when Gaussian elimination is a familiar or efficient approach. It is suitable for matrices where direct cofactor expansion is computationally too expensive.
#   • Idea: This algorithm computes the determinant of a square matrix by transforming it into an upper triangular form using Gaussian elimination. The determinant is the product of diagonal elements, adjusted by a sign factor from row swaps, with O(N^3) complexity.
#   • Invariants: Before processing column 'k', all elements A[i][j] where i > j and j < k are zero.; The determinant of the current matrix, multiplied by (-1)^swaps, equals the original matrix's determinant.
#   • Tips: Track the number of row swaps to correctly determine the determinant's sign.; Pivot selection can improve numerical stability, especially with floating-point numbers.
#   • Pitfalls: Forgetting to adjust the sign after row exchanges.; Division by zero if a pivot element is zero, requiring a row swap.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def decodeCiphertext(self, encodedText, rows):
        """
        :type encodedText: str
        :type rows: int
        :rtype: str
        """
        n = len(encodedText)
        cols = n // rows
        matrix = [[''] * cols for _ in range(rows)]
        
        index = 0
        for r in range(rows):
            for c in range(cols):
                matrix[r][c] = encodedText[index]
                index += 1
        
        result = []
        for c in range(cols):
            r = 0
            curr_c = c
            while r < rows and curr_c < cols:
                result.append(matrix[r][curr_c])
                r += 1
                curr_c += 1
        
        decoded_text = ''.join(result).rstrip()
        return decoded_text