# Source: https://leetcode.com/problems/minimum-genetic-mutation/   |   Difficulty: Medium
#
# Problem Description:
# A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.
#
# Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene where one mutation is defined as one single character changed in the gene string.
#
#
# 	For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
#
#
# There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.
#
# Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of mutations needed to mutate from startGene to endGene. If there is no such a mutation, return -1.
#
# Note that the starting point is assumed to be valid, so it might not be included in the bank.
#
# Example:
# Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
# Output: 1
#
# Constraints:
# 0 <= bank.length <= 10
# 	startGene.length == endGene.length == bank[i].length == 8
# 	startGene, endGene, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].
#

class Solution(object):
    def minMutation(self, startGene, endGene, bank):
        """
        :type startGene: str
        :type endGene: str
        :type bank: List[str]
        :rtype: int
        """
        from collections import deque

        bank_set = set(bank)
        if endGene not in bank_set:
            return -1

        def get_neighbors(gene):
            neighbors = []
            for i in range(len(gene)):
                for c in 'ACGT':
                    if c != gene[i]:
                        mutated = gene[:i] + c + gene[i+1:]
                        if mutated in bank_set:
                            neighbors.append(mutated)
            return neighbors

        queue = deque([(startGene, 0)])
        visited = set([startGene])

        while queue:
            current_gene, mutations = queue.popleft()
            if current_gene == endGene:
                return mutations

            for neighbor in get_neighbors(current_gene):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, mutations + 1))

        return -1