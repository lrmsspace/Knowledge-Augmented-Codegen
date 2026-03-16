# Source: https://leetcode.com/problems/defuse-the-bomb/   |   Difficulty: Easy
#
# Problem Description:
# You have a bomb to defuse, and your time is running out! Your informer will provide you with a circular array code of length of n and a key k.
#
# To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.
#
#
# 	If k > 0, replace the ith number with the sum of the next k numbers.
# 	If k < 0, replace the ith number with the sum of the previous k numbers.
# 	If k == 0, replace the ith number with 0.
#
#
# As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].
#
# Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!
#
# Example:
# Input: code = [5,7,1,4], k = 3
# Output: [12,10,16,13]
# Explanation: Each number is replaced by the sum of the next 3 numbers. The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.
#
# Constraints:
# n == code.length
# 	1 <= n <= 100
# 	1 <= code[i] <= 100
# 	-(n - 1) <= k <= n - 1
#
# Helpful references (internal KB):
# - Reservoir Sampling (array, randomized, simulation)
#   • When to use: When you need to randomly select a fixed number of items (k) from a stream or a very large dataset of unknown size, ensuring each item has an equal probability of selection in a single pass.
#   • Idea: Reservoir sampling is a randomized algorithm that selects k items from a list containing n items, where n is either a very large or unknown number, ensuring each item has an equal probability of being selected. It processes the input in a single pass with O(N) time complexity and O(k) space complexity.
#   • Invariants: The reservoir always contains exactly k elements.; Any element processed up to the current index `i` has a k/(i+1) probability of being in the reservoir.
#   • Tips: Initialize the reservoir with the first k elements from the stream.; For each subsequent element, generate a random index from 0 to current_stream_index.
#   • Pitfalls: Failing to correctly initialize the reservoir with the first k elements.; Generating random indices outside the valid range [0, current_stream_index] or [0, k-1].
# - Finding the rank of a matrix (matrix, simulation, enumeration)
#   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
#   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
#   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
#   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
#   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
# - Gauss method for solving system of linea (matrix, number, simulation)
#   • When to use: Use to solve systems of linear equations, determine matrix rank, or find matrix inverses. It helps analyze if a system has unique, infinite, or no solutions.
#   • Idea: Gaussian elimination transforms an augmented matrix into row echelon form using elementary row operations to solve linear systems. Gauss-Jordan extends this to reduced row echelon form for direct solutions, typically with O(N^3) complexity.
#   • Invariants: The solution set of the system of equations remains unchanged after each elementary row operation.; After processing column k, all elements below the pivot in that column are zero.
#   • Tips: Use partial pivoting to improve numerical stability and avoid division by zero.; Handle floating-point precision issues carefully, using a small epsilon for comparisons.
#   • Pitfalls: Encountering division by zero if a pivot element is zero and no pivoting is applied.; Numerical instability and accumulation of floating-point errors, especially without pivoting.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def decrypt(self, code, k):
        """
        :type code: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(code)
        decrypted = [0] * n
        
        for i in range(n):
            if k > 0:
                decrypted[i] = sum(code[(i + j) % n] for j in range(1, k + 1))
            elif k < 0:
                decrypted[i] = sum(code[(i - j) % n] for j in range(1, -k + 1))
            else:  # k == 0
                decrypted[i] = 0
        
        return decrypted