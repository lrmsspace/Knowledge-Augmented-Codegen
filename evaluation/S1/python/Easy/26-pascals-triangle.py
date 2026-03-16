# Source: https://leetcode.com/problems/pascals-triangle/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer numRows, return the first numRows of Pascal's triangle.
#
# In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
#
# Example:
# Input: numRows = 5
# Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
#
# Constraints:
# 1 <= numRows <= 30
#
# Helpful references (internal KB):
# - Binomial Coefficients (number, enumeration)
#   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
#   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
#   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
#   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
#   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
# - Gauss method for solving system of linea (bitset, matrix, simulation)
#   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
#   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
#   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
#   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
#   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def generate(self, numRows):
        """
        :type numRows: int
        :rtype: List[List[int]]
        """
        triangle = []

        for row_num in range(numRows):
            row = [1] * (row_num + 1)

            for j in range(1, row_num):
                row[j] = triangle[row_num - 1][j - 1] + triangle[row_num - 1][j]

            triangle.append(row)

        return triangle