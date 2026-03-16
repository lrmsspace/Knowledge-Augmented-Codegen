# Source: https://leetcode.com/problems/shortest-distance-after-road-addition-queries-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and a 2D integer array queries.
#
# There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.
#
# queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.
#
# There are no two queries such that queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
#
# Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.
#
# Example:
# Input: n = 5, queries = [[2,4],[0,2],[0,4]]
#
# Output: [3,2,1]
#
# Explanation: 
#
#
#
# After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
#
#
#
# After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
#
#
#
# After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.
#
# Constraints:
# 3 <= n <= 105
# 	1 <= queries.length <= 105
# 	queries[i].length == 2
# 	0 <= queries[i][0] < queries[i][1] < n
# 	1 < queries[i][1] - queries[i][0]
# 	There are no repeated roads among the queries.
# 	There are no two queries such that i != j and queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
#
# Helpful references (internal KB):
# - Range Minimum Query (array, tree, segment-tree)
#   • When to use: Use when needing to efficiently query minimums over arbitrary ranges and perform point or range updates on an array.
#   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and performing updates in logarithmic time, typically O(log N) for both.
#   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; A parent node's value is derived from its children's values (e.g., minimum of children).
#   • Tips: Build the tree recursively, dividing the array into halves until leaf nodes are reached.; Query operations involve traversing relevant segments, combining results from child nodes.
#   • Pitfalls: Incorrectly handling array indexing (0-based vs. 1-based) can lead to off-by-one errors.; Forgetting to update parent nodes after a child's value changes during an update operation.
# - Dijkstra Algorithm (graph, array, dijkstra, greedy)
#   • When to use: Use this algorithm to find the shortest paths from a single source to all other vertices in a graph. It is applicable when all edge weights are non-negative.
#   • Idea: Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It iteratively selects the unvisited vertex with the smallest known distance, relaxing its outgoing edges, achieving O(V^2 + E) or O(E log V) complexity.
#   • Invariants: For any marked vertex v, d[v] holds the true shortest path distance from s to v.; For any unmarked vertex v, d[v] holds the shortest path distance from s to v using only marked intermediate vertices.
#   • Tips: Use a priority queue for sparse graphs to optimize performance to O(E log V).; Initialize distances to infinity for all vertices except the source, which is zero.
#   • Pitfalls: Dijkstra's algorithm does not work correctly with negative edge weights; use Bellman-Ford or SPFA instead.; Failing to use an efficient data structure (like a priority queue) for vertex selection can lead to O(V^2) performance on sparse graphs.
# - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
#   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
#   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
#   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
#   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
#   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shortestDistanceAfterQueries(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # The shortest path from city 0 to city n - 1 is initially n - 1 (the direct path through the existing roads).
        # Each query adds a new road that can potentially shorten the path.
        # We can keep track of the shortest path length after each query by maintaining a variable that updates based on the new road added.
        
        shortest_paths = []
        current_shortest = n - 1  # Initial shortest path length
        
        for ui, vi in queries:
            # If the new road from ui to vi creates a shorter path from 0 to n - 1, update the current shortest path
            if ui == 0 and vi == n - 1:
                current_shortest = 1
            elif ui == 0:
                current_shortest = min(current_shortest, vi + 1)
            elif vi == n - 1:
                current_shortest = min(current_shortest, n - ui)
            else:
                # Check if this new road can create a shorter path through it
                if ui < current_shortest and vi > current_shortest:
                    current_shortest = min(current_shortest, ui + (n - vi))
            
            shortest_paths.append(current_shortest)
        
        return shortest_paths