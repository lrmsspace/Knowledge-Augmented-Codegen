# Source: https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/   |   Difficulty: Hard
#
# Problem Description:
# Given a matrix and a target, return the number of non-empty submatrices that sum to target.
#
# A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
#
# Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
#
# Example:
# Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
# Output: 4
# Explanation: The four 1x1 submatrices that only contain 0.
#
# Constraints:
# 1 <= matrix.length <= 100
# 	1 <= matrix[0].length <= 100
# 	-1000 <= matrix[i][j] <= 1000
# 	-10^8 <= target <= 10^8
#

class Solution(object):
    def numSubmatrixSumTarget(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: int
        """
        from collections import defaultdict

        rows, cols = len(matrix), len(matrix[0])
        prefix_sums = [[0] * (cols + 1) for _ in range(rows + 1)]

        for r in range(1, rows + 1):
            for c in range(1, cols + 1):
                prefix_sums[r][c] = (matrix[r - 1][c - 1] +
                                     prefix_sums[r - 1][c] +
                                     prefix_sums[r][c - 1] -
                                     prefix_sums[r - 1][c - 1])

        count = 0
        for r1 in range(1, rows + 1):
            for r2 in range(r1, rows + 1):
                sum_count = defaultdict(int)
                sum_count[0] = 1
                for c in range(1, cols + 1):
                    curr_sum = (prefix_sums[r2][c] - prefix_sums[r1 - 1][c])
                    if curr_sum - target in sum_count:
                        count += sum_count[curr_sum - target]
                    sum_count[curr_sum] += 1

        return count