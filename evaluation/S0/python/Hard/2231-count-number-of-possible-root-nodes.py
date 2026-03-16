# Source: https://leetcode.com/problems/count-number-of-possible-root-nodes/   |   Difficulty: Hard
#
# Problem Description:
# Alice has an undirected tree with n nodes labeled from 0 to n - 1. The tree is represented as a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# Alice wants Bob to find the root of the tree. She allows Bob to make several guesses about her tree. In one guess, he does the following:
#
#
# 	Chooses two distinct integers u and v such that there exists an edge [u, v] in the tree.
# 	He tells Alice that u is the parent of v in the tree.
#
#
# Bob's guesses are represented by a 2D integer array guesses where guesses[j] = [uj, vj] indicates Bob guessed uj to be the parent of vj.
#
# Alice being lazy, does not reply to each of Bob's guesses, but just says that at least k of his guesses are true.
#
# Given the 2D integer arrays edges, guesses and the integer k, return the number of possible nodes that can be the root of Alice's tree. If there is no such tree, return 0.
#
# Example:
# Input: edges = [[0,1],[1,2],[1,3],[4,2]], guesses = [[1,3],[0,1],[1,0],[2,4]], k = 3
# Output: 3
# Explanation: 
# Root = 0, correct guesses = [1,3], [0,1], [2,4]
# Root = 1, correct guesses = [1,3], [1,0], [2,4]
# Root = 2, correct guesses = [1,3], [1,0], [2,4]
# Root = 3, correct guesses = [1,0], [2,4]
# Root = 4, correct guesses = [1,3], [1,0]
# Considering 0, 1, or 2 as root node leads to 3 correct guesses.
#
# Constraints:
# edges.length == n - 1
# 	2 <= n <= 105
# 	1 <= guesses.length <= 105
# 	0 <= ai, bi, uj, vj <= n - 1
# 	ai != bi
# 	uj != vj
# 	edges represents a valid tree.
# 	guesses[j] is an edge of the tree.
# 	guesses is unique.
# 	0 <= k <= guesses.length
#

class Solution(object):
    def rootCount(self, edges, guesses, k):
        """
        :type edges: List[List[int]]
        :type guesses: List[List[int]]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        n = len(edges)
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        guess_set = set((u, v) for u, v in guesses)

        def dfs(node, parent):
            count = 0
            for neighbor in tree[node]:
                if neighbor != parent:
                    if (node, neighbor) in guess_set:
                        count += 1
                    count += dfs(neighbor, node)
            return count

        correct_guesses = dfs(0, -1)

        result = 0

        def reroot(node, parent, current_correct):
            nonlocal result
            if current_correct >= k:
                result += 1
            for neighbor in tree[node]:
                if neighbor != parent:
                    new_correct = current_correct
                    if (node, neighbor) in guess_set:
                        new_correct -= 1
                    if (neighbor, node) in guess_set:
                        new_correct += 1
                    reroot(neighbor, node, new_correct)

        reroot(0, -1, correct_guesses)

        return result