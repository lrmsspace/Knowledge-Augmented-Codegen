# Source: https://leetcode.com/problems/maximum-genetic-difference-query/   |   Difficulty: Hard
#
# Problem Description:
# There is a rooted tree consisting of n nodes numbered 0 to n - 1. Each node's number denotes its unique genetic value (i.e. the genetic value of node x is x). The genetic difference between two genetic values is defined as the bitwise-XOR of their values. You are given the integer array parents, where parents[i] is the parent for node i. If node x is the root of the tree, then parents[x] == -1.
#
# You are also given the array queries where queries[i] = [nodei, vali]. For each query i, find the maximum genetic difference between vali and pi, where pi is the genetic value of any node that is on the path between nodei and the root (including nodei and the root). More formally, you want to maximize vali XOR pi.
#
# Return an array ans where ans[i] is the answer to the ith query.
#
# Example:
# Input: parents = [-1,0,1,1], queries = [[0,2],[3,2],[2,5]]
# Output: [2,3,7]
# Explanation: The queries are processed as follows:
# - [0,2]: The node with the maximum genetic difference is 0, with a difference of 2 XOR 0 = 2.
# - [3,2]: The node with the maximum genetic difference is 1, with a difference of 2 XOR 1 = 3.
# - [2,5]: The node with the maximum genetic difference is 2, with a difference of 5 XOR 2 = 7.
#
# Constraints:
# 2 <= parents.length <= 105
# 	0 <= parents[i] <= parents.length - 1 for every node i that is not the root.
# 	parents[root] == -1
# 	1 <= queries.length <= 3 * 104
# 	0 <= nodei <= parents.length - 1
# 	0 <= vali <= 2 * 105
#

class Solution(object):
    def maxGeneticDifference(self, parents, queries):
        """
        :type parents: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(parents)
        tree = [[] for _ in range(n)]
        root = -1
        for i in range(n):
            if parents[i] == -1:
                root = i
            else:
                tree[parents[i]].append(i)

        q_map = [[] for _ in range(n)]
        for i, (node, val) in enumerate(queries):
            q_map[node].append((val, i))

        class TrieNode:
            def __init__(self):
                self.children = {}
                self.count = 0

        class Trie:
            def __init__(self):
                self.root = TrieNode()

            def insert(self, num):
                node = self.root
                for i in range(17, -1, -1):
                    bit = (num >> i) & 1
                    if bit not in node.children:
                        node.children[bit] = TrieNode()
                    node = node.children[bit]
                    node.count += 1

            def remove(self, num):
                node = self.root
                for i in range(17, -1, -1):
                    bit = (num >> i) & 1
                    child = node.children[bit]
                    child.count -= 1
                    if child.count == 0:
                        del node.children[bit]
                        return
                    node = child

            def max_xor(self, num):
                node = self.root
                xor_sum = 0
                for i in range(17, -1, -1):
                    bit = (num >> i) & 1
                    toggled_bit = 1 - bit
                    if toggled_bit in node.children:
                        xor_sum |= (1 << i)
                        node = node.children[toggled_bit]
                    else:
                        node = node.children.get(bit, node)
                return xor_sum

        trie = Trie()
        res = [0] * len(queries)

        def dfs(u):
            trie.insert(u)
            for val, idx in q_map[u]:
                res[idx] = trie.max_xor(val)
            for v in tree[u]:
                dfs(v)
            trie.remove(u)

        dfs(root)
        return res