# Source: https://leetcode.com/problems/valid-arrangement-of-pairs/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
#
# Return any valid arrangement of pairs.
#
# Note: The inputs will be generated such that there exists a valid arrangement of pairs.
#
# Example:
# Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
# Output: [[11,9],[9,4],[4,5],[5,1]]
# Explanation:
# This is a valid arrangement since endi-1 always equals starti.
# end0 = 9 == 9 = start1 
# end1 = 4 == 4 = start2
# end2 = 5 == 5 = start3
#
# Constraints:
# 1 <= pairs.length <= 105
# 	pairs[i].length == 2
# 	0 <= starti, endi <= 109
# 	starti != endi
# 	No two pairs are exactly the same.
# 	There exists a valid arrangement of pairs.
#

class Solution(object):
    def validArrangement(self, pairs):
        """
        :type pairs: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict, deque

        graph = defaultdict(deque)
        in_degree = defaultdict(int)
        out_degree = defaultdict(int)

        for u, v in pairs:
            graph[u].append(v)
            out_degree[u] += 1
            in_degree[v] += 1

        start_node = pairs[0][0]
        for node in out_degree:
            if out_degree[node] - in_degree[node] == 1:
                start_node = node
                break

        stack = [start_node]
        result = []

        while stack:
            u = stack[-1]
            if graph[u]:
                v = graph[u].pop()
                stack.append(v)
            else:
                result.append(stack.pop())

        return result[::-1]