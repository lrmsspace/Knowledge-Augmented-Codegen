# Source: https://leetcode.com/problems/minimum-cost-to-convert-string-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].
#
# You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.
#
# Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.
#
# Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
#
# Example:
# Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
# Output: 28
# Explanation: To convert the string "abcd" to string "acbe":
# - Change value at index 1 from 'b' to 'c' at a cost of 5.
# - Change value at index 2 from 'c' to 'e' at a cost of 1.
# - Change value at index 2 from 'e' to 'b' at a cost of 2.
# - Change value at index 3 from 'd' to 'e' at a cost of 20.
# The total cost incurred is 5 + 1 + 2 + 20 = 28.
# It can be shown that this is the minimum possible cost.
#
# Constraints:
# 1 <= source.length == target.length <= 105
# 	source, target consist of lowercase English letters.
# 	1 <= cost.length == original.length == changed.length <= 2000
# 	original[i], changed[i] are lowercase English letters.
# 	1 <= cost[i] <= 106
# 	original[i] != changed[i]
#

class Solution(object):
    def minimumCost(self, source, target, original, changed, cost):
        """
        :type source: str
        :type target: str
        :type original: List[str]
        :type changed: List[str]
        :type cost: List[int]
        :rtype: int
        """
        from collections import defaultdict
        import heapq

        graph = defaultdict(list)
        for o, c, co in zip(original, changed, cost):
            graph[o].append((c, co))

        def dijkstra(start, end):
            heap = [(0, start)]
            visited = set()
            while heap:
                curr_cost, node = heapq.heappop(heap)
                if node == end:
                    return curr_cost
                if node in visited:
                    continue
                visited.add(node)
                for neighbor, edge_cost in graph[node]:
                    if neighbor not in visited:
                        heapq.heappush(heap, (curr_cost + edge_cost, neighbor))
            return float('inf')

        total_cost = 0
        for s_char, t_char in zip(source, target):
            if s_char == t_char:
                continue
            cost_to_convert = dijkstra(s_char, t_char)
            if cost_to_convert == float('inf'):
                return -1
            total_cost += cost_to_convert

        return total_cost