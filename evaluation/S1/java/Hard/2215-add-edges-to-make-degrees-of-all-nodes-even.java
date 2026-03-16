// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
//
// You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
//
// The degree of a node is the number of edges connected to it.
//
// Example:
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
//
// Constraints:
// 3 <= n <= 105
// 	2 <= edges.length <= 105
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private void toggleNode(Set<Integer> oddDegreeNodes, int node) {
        if (oddDegreeNodes.contains(node)) {
            oddDegreeNodes.remove(node);
        } else {
            oddDegreeNodes.add(node);
        }
    }
    private long getEdgeKey(int u, int v) {
        return ((long) Math.min(u, v) << 32) | Math.max(u, v);
    }
    public boolean isPossible(int n, List<List<Integer>> edges) {
        Set<Integer> oddDegreeNodes = new HashSet<>();
        Set<Long> existingEdges = new HashSet<>();

        for (List<Integer> edge : edges) {
            int u = edge.get(0);
            int v = edge.get(1);

            long edgeKey = ((long) Math.min(u, v) << 32) | Math.max(u, v);
            existingEdges.add(edgeKey);

            toggleNode(oddDegreeNodes, u);
            toggleNode(oddDegreeNodes, v);
        }

        int oddCount = oddDegreeNodes.size();
        if (oddCount == 0) {
            return true;
        } else if (oddCount == 2) {
            Integer[] oddNodes = oddDegreeNodes.toArray(new Integer[0]);
            int a = oddNodes[0];
            int b = oddNodes[1];
            long edgeKey = ((long) Math.min(a, b) << 32) | Math.max(a, b);
            return !existingEdges.contains(edgeKey);
        } else if (oddCount == 4) {
            Integer[] oddNodes = oddDegreeNodes.toArray(new Integer[0]);
            int a = oddNodes[0], b = oddNodes[1], c = oddNodes[2], d = oddNodes[3];

            return (!existingEdges.contains(getEdgeKey(a, b)) && !existingEdges.contains(getEdgeKey(c, d))) ||
                   (!existingEdges.contains(getEdgeKey(a, c)) && !existingEdges.contains(getEdgeKey(b, d))) ||
                   (!existingEdges.contains(getEdgeKey(a, d)) && !existingEdges.contains(getEdgeKey(b, c)));
        } else {
            return false;
        }           
    }
}
