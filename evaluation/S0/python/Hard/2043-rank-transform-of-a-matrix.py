# Source: https://leetcode.com/problems/rank-transform-of-a-matrix/   |   Difficulty: Hard
#
# Problem Description:
# Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].
#
# The rank is an integer that represents how large an element is compared to other elements. It is calculated using the following rules:
#
#
# 	The rank is an integer starting from 1.
# 	If two elements p and q are in the same row or column, then:
# 	
# 		If p < q then rank(p) < rank(q)
# 		If p == q then rank(p) == rank(q)
# 		If p > q then rank(p) > rank(q)
# 	
# 	
# 	The rank should be as small as possible.
#
#
# The test cases are generated so that answer is unique under the given rules.
#
# Example:
# Input: matrix = [[1,2],[3,4]]
# Output: [[1,2],[2,3]]
# Explanation:
# The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
# The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][0] is rank 1.
# The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1.
# The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and both matrix[0][1] and matrix[1][0] are rank 2.
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	1 <= m, n <= 500
# 	-109 <= matrix[row][col] <= 109
#

class Solution(object):
    def matrixRankTransform(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict

        m, n = len(matrix), len(matrix[0])
        value_positions = defaultdict(list)

        for i in range(m):
            for j in range(n):
                value_positions[matrix[i][j]].append((i, j))

        rank = [0] * (m + n)
        answer = [[0] * n for _ in range(m)]

        for value in sorted(value_positions):
            parent = list(range(m + n))
            size = [1] * (m + n)

            def find(x):
                while parent[x] != x:
                    parent[x] = parent[parent[x]]
                    x = parent[x]
                return x

            def union(x, y):
                rootX = find(x)
                rootY = find(y)
                if rootX != rootY:
                    if size[rootX] < size[rootY]:
                        rootX, rootY = rootY, rootX
                    parent[rootY] = rootX
                    size[rootX] += size[rootY]

            for i, j in value_positions[value]:
                union(i, j + m)

            group_max_rank = {}
            for i, j in value_positions[value]:
                root = find(i)
                group_max_rank[root] = max(group_max_rank.get(root, 0), rank[i], rank[j + m])

            for i, j in value_positions[value]:
                root = find(i)
                answer[i][j] = group_max_rank[root] + 1

            for i, j in value_positions[value]:
                rank[i] = answer[i][j]
                rank[j + m] = answer[i][j]

        return answer