# Source: https://leetcode.com/problems/sum-of-matrix-after-queries/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n and a 0-indexed 2D array queries where queries[i] = [typei, indexi, vali].
#
# Initially, there is a 0-indexed n x n matrix filled with 0's. For each query, you must apply one of the following changes:
#
#
# 	if typei == 0, set the values in the row with indexi to vali, overwriting any previous values.
# 	if typei == 1, set the values in the column with indexi to vali, overwriting any previous values.
#
#
# Return the sum of integers in the matrix after all queries are applied.
#
# Example:
# Input: n = 3, queries = [[0,0,1],[1,2,2],[0,2,3],[1,0,4]]
# Output: 23
# Explanation: The image above describes the matrix after each query. The sum of the matrix after all queries are applied is 23.
#
# Constraints:
# 1 <= n <= 104
# 	1 <= queries.length <= 5 * 104
# 	queries[i].length == 3
# 	0 <= typei <= 1
# 	0 <= indexi < n
# 	0 <= vali <= 105
#
# Helpful references (internal KB):
# - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
#   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
#   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
#   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
#   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
#   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
# - Sieve of Eratosthenes (array, sieve, enumeration)
#   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
#   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
#   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
#   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
# - Sqrt Decomposition (array, enumeration, prefix-sum)
#   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
#   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
#   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
#   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def matrixSumQueries(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: int
        """
        row_sum = [0] * n
        col_sum = [0] * n
        row_updated = set()
        col_updated = set()
        total_sum = 0

        for t, idx, val in reversed(queries):
            if t == 0:  # Row update
                if idx not in row_updated:
                    total_sum += val * (n - len(col_updated))  # Only add for columns not updated
                    row_updated.add(idx)
            else:  # Column update
                if idx not in col_updated:
                    total_sum += val * (n - len(row_updated))  # Only add for rows not updated
                    col_updated.add(idx)

        return total_sum