// Source: https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected weighted graph with n vertices labeled from 0 to n - 1.
//
// You are given the integer n and an array edges, where edges[i] = [ui, vi, wi] indicates that there is an edge between vertices ui and vi with a weight of wi.
//
// A walk on a graph is a sequence of vertices and edges. The walk starts and ends with a vertex, and each edge connects the vertex that comes before it and the vertex that comes after it. It's important to note that a walk may visit the same edge or vertex more than once.
//
// The cost of a walk starting at node u and ending at node v is defined as the bitwise AND of the weights of the edges traversed during the walk. In other words, if the sequence of edge weights encountered during the walk is w0, w1, w2, ..., wk, then the cost is calculated as w0 & w1 & w2 & ... & wk, where & denotes the bitwise AND operator.
//
// You are also given a 2D array query, where query[i] = [si, ti]. For each query, you need to find the minimum cost of the walk starting at vertex si and ending at vertex ti. If there exists no such walk, the answer is -1.
//
// Return the array answer, where answer[i] denotes the minimum cost of a walk for query i.
//
// Example:
// Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
//
// Output: [1,-1]
//
// Explanation:
//
// To achieve the cost of 1 in the first query, we need to move on the following edges: 0->1 (weight 7), 1->2 (weight 1), 2->1 (weight 1), 1->3 (weight 7).
//
// In the second query, there is no walk between nodes 3 and 4, so the answer is -1.
//
// Constraints:
// 2 <= n <= 105
// 	0 <= edges.length <= 105
// 	edges[i].length == 3
// 	0 <= ui, vi <= n - 1
// 	ui != vi
// 	0 <= wi <= 105
// 	1 <= query.length <= 105
// 	query[i].length == 2
// 	0 <= si, ti <= n - 1
// 	si != ti
//
// Helpful references (internal KB):
// - Finding Bridges Online (graph, tree, union-find, counting)
//   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
//   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
//   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
//   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
//   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minimumCost(int n, int** edges, int edgesSize, int* edgesColSize, int** query, int querySize, int* queryColSize, int* returnSize) {
  
    // Build adjacency list
    int adjSizes[100000];
    int* adj[100000];
    memset(adjSizes, 0, sizeof(adjSizes));
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adjSizes[u]++; adjSizes[v]++;
    }
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int) * 2);
        adjSizes[i] = 0;
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        adj[u][adjSizes[u]++] = v; adj[u][adjSizes[u]++] = w;
        adj[v][adjSizes[v]++] = u; adj[v][adjSizes[v]++] = w;
    }

    // Process each query
    int* result = (int*)malloc(querySize * sizeof(int));
    for (int q = 0; q < querySize; ++q) {
        int source = query[q][0], destination = query[q][1];
        // Dijkstra's algorithm to find minimum cost walk
        int dist[100000];
        for (int i = 0; i < n; ++i) dist[i] = -1;
        dist[source] = 0;

        // Min-heap priority queue
        typedef struct {
            int node;
            int cost;
        } HeapNode;
        HeapNode heap[100000];
        int heapSize = 0;

        // Push function
        void push(int node, int cost) {
            heap[heapSize].node = node;
            heap[heapSize].cost = cost;
            int idx = heapSize++;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (heap[parent].cost <= heap[idx].cost) break;
                HeapNode temp = heap[parent];
                heap[parent] = heap[idx];
                heap[idx] = temp;
                idx = parent;
            }
        }

        // Pop function
        HeapNode pop() {
            HeapNode top = heap[0];
            heap[0] = heap[--heapSize];
            int idx = 0;    
            while (1) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int smallest = idx;
                if (left < heapSize && heap[left].cost < heap[smallest].cost) {
                    smallest = left;
                }
                if (right < heapSize && heap[right].cost < heap[smallest].cost) {
                    smallest = right;
                }
                if (smallest == idx) break;
                HeapNode temp = heap[smallest];
                heap[smallest] = heap[idx];
                heap[idx] = temp;
                idx = smallest;
            }
            return top;
        }
        push(source, 0);
        while (heapSize) {
            HeapNode node = pop();
            int u = node.node, cost = node.cost;
            if (cost > dist[u]) continue;
            for (int i = 0; i < adjSizes[u]; i += 2) {
                int v = adj[u][i];
                int w = adj[u][i + 1];
                int newCost = (dist[u] == 0) ? w : (dist[u] & w);
                if (dist[v] == -1 || newCost < dist[v]) {
                    dist[v] = newCost;
                    push(v, newCost);
                }
            }
        }
        result[q] = dist[destination];
        for (int i = 0; i < n; ++i) {       
            free(adj[i]);
        }
    }
    *returnSize = querySize;
    return result;
}
