# Source: https://leetcode.com/problems/number-of-paths-with-max-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.
#
# You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
#
# Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.
#
# In case there is no path, return [0, 0].
#
# Example:
# Input: board = ["E23","2X2","12S"]
# Output: [7,1]
#
# Constraints:
# 2 <= board.length == board[i].length <= 100
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
#   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
#   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
#   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
#   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
#   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
# - Fibonacci Numbers (number, recursion, binary-lifting)
#   • When to use: Use when computing the N-th Fibonacci number for extremely large N, or when the result needs to be calculated modulo a specific value, requiring logarithmic time complexity.
#   • Idea: This method computes the N-th Fibonacci number by leveraging matrix exponentiation or specific doubling identities, reducing the problem size by half in each step. It achieves an O(log N) time complexity.
#   • Invariants: The function `compute(n)` always returns the pair `(F_n, F_{n+1})`.; For any `k`, the values `F_k` and `F_{k+1}` are correctly computed before deriving `F_{2k}` and `F_{2k+1}`.
#   • Tips: Utilize matrix exponentiation for a general and robust approach.; The doubling identities F_2k+1 and F_2k can be faster than explicit matrix multiplication.
#   • Pitfalls: Integer overflow if modulo arithmetic or arbitrary-precision integers are not used for large N.; Incorrectly defining base cases in the recursive implementation can lead to errors.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def pathsWithMaxScore(self, board):
        """
        :type board: List[str]
        :rtype: List[int]
        """
        MOD = 10**9 + 7
        n = len(board)
        dp = [[(-1, 0)] * n for _ in range(n)]  # (max_score, count)

        def dfs(r, c):
            if r < 0 or c < 0 or board[r][c] == 'X':
                return (-1, 0)
            if (r, c) == (n - 1, n - 1):
                return (0, 1)
            if dp[r][c][0] != -1:
                return dp[r][c]

            max_score = -1
            count = 0
            for dr, dc in [(-1, 0), (0, -1), (-1, -1)]:
                score, cnt = dfs(r + dr, c + dc)
                if score > max_score:
                    max_score = score
                    count = cnt
                elif score == max_score:
                    count = (count + cnt) % MOD

            if board[r][c] not in 'SE':
                max_score += int(board[r][c])
            dp[r][c] = (max_score, count)
            return dp[r][c]

        result = dfs(0, 0)
        return [result[0], result[1]] if result[0] >= 0 else [0, 0]