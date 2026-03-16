# Source: https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n matrix mat that has its rows sorted in non-decreasing order and an integer k.
#
# You are allowed to choose exactly one element from each row to form an array.
#
# Return the kth smallest array sum among all possible arrays.
#
# Example:
# Input: mat = [[1,3,11],[2,4,6]], k = 5
# Output: 7
# Explanation: Choosing one element from each row, the first k smallest sum are:
# [1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.
#
# Constraints:
# m == mat.length
# 	n == mat.length[i]
# 	1 <= m, n <= 40
# 	1 <= mat[i][j] <= 5000
# 	1 <= k <= min(200, nm)
# 	mat[i] is a non-decreasing array.
#

class Solution(object):
    def kthSmallest(self, mat, k):
        """
        :type mat: List[List[int]]
        :type k: int
        :rtype: int
        """
        import heapq
        m, n = len(mat), len(mat[0])
        min_heap = [(sum(row[0] for row in mat), [0] * m)]
        visited = set()
        visited.add(tuple([0] * m))

        while min_heap:
            current_sum, indices = heapq.heappop(min_heap)
            k -= 1
            if k == 0:
                return current_sum

            for i in range(m):
                if indices[i] + 1 < n:
                    new_indices = indices[:]
                    new_indices[i] += 1
                    new_tuple = tuple(new_indices)
                    if new_tuple not in visited:
                        new_sum = current_sum - mat[i][indices[i]] + mat[i][new_indices[i]]
                        heapq.heappush(min_heap, (new_sum, new_indices))
                        visited.add(new_tuple)