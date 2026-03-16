// Source: https://leetcode.com/problems/modify-graph-edge-weights/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).
//
// Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.
//
// Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.
//
// Note: You are not allowed to modify the weights of edges with initial positive weights.
//
// Example:
// Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
// Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
// Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 3
// 	0 <= ai, bi < n
// 	wi = -1 or 1 <= wi <= 107
// 	ai != bi
// 	0 <= source, destination < n
// 	source != destination
// 	1 <= target <= 109
// 	The graph is connected, and there are no self-loops or repeated edges
//
// Helpful references (internal KB):
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, number, greedy, dijkstra, bellman-ford)
//   • When to use: When you need to find a flow of a certain amount (or maximum possible flow) through a network while minimizing the total cost associated with sending flow along edges. It is suitable for problems involving resource allocation with varying costs.
//   • Idea: The successive shortest path algorithm finds a minimum-cost flow by repeatedly finding a shortest augmenting path in the residual graph and pushing flow along it. Its complexity depends on the shortest path algorithm used (Bellman-Ford for general costs, Dijkstra with potentials for non-negative residual costs).
//   • Invariants: At the start of each iteration, the current flow is a valid flow from source to sink.; The residual graph correctly represents remaining capacities and reverse edges for the current flow.
//   • Tips: Use potentials (reduced costs) with Dijkstra to efficiently handle non-negative edge costs in the residual graph.; Initialize potentials to zero and update them after each shortest path computation.
//   • Pitfalls: Incorrectly updating residual capacities or reverse edge costs can lead to wrong results.; Failing to use potentials with Dijkstra can lead to incorrect shortest paths in graphs with negative edges.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** modifiedGraphEdges(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination, int target, int* returnSize, int** returnColumnSizes) {
 
    /* Build adjacency list */
    int adjSizes[100];
    int* adj[100];
    memset(adjSizes, 0, sizeof(adjSizes));
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adjSizes[u]++; adjSizes[v]++;
    }
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int));
        adjSizes[i] = 0; /* reuse for current size */
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    /* Helper function: Dijkstra's algorithm */
    #define INF 0x3f3f3f3f
    int dist[100];
    void dijkstra(int src, int n, int (*getWeight)(int, int)) {
        for (int i = 0; i < n; ++i)
            dist[i] = INF;
        dist[src] = 0;

        typedef struct {
            int node;
            int distance;
        } Node;

        #define MAX_NODES 10000
        Node heap[MAX_NODES];
        int heapSize = 0;

        void push(int node, int distance) {
            heap[++heapSize] = (Node){node, distance};
            int idx = heapSize;
            while (idx > 1) {
                int parent = idx / 2;
                if (heap[parent].distance <= heap[idx].distance) break;
                Node tmp = heap[parent];
                heap[parent] = heap[idx];
                heap[idx] = tmp;
                idx = parent;
            }
        }

        Node pop() {
            Node top = heap[1];
            heap[1] = heap[heapSize--];
            int idx = 1;
            while (1) {
                int left = idx * 2, right = idx * 2 + 1, smallest = idx;
                if (left <= heapSize && heap[left].distance < heap[smallest].distance)
                    smallest = left;
                if (right <= heapSize && heap[right].distance < heap[smallest].distance)
                    smallest = right;
                if (smallest == idx) break;
                Node tmp = heap[smallest];
                heap[smallest] = heap[idx];
                heap[idx] = tmp;
                idx = smallest;
            }
            return top;
        }
        push(src, 0);
        while (heapSize) {
            Node node = pop();
            int u = node.node, d = node.distance;
            if (d > dist[u]) continue;
            for (int i = 0; i < adjSizes[u]; ++i) {
                int v = adj[u][i];
                int weight = getWeight(u, v);
                if (weight < 0) continue; // Ignore -1 weights
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    push(v, dist[v]);
                }
            }
        }
    }
    /* Get weight function */
    int getWeight(int u, int v) {
        for (int i = 0; i < edgesSize; ++i) {
            if ((edges[i][0] == u && edges[i][1] == v) || (edges[i][0] == v && edges[i][1] == u)) {
                return edges[i][2];
            }
        }
        return -1; // Should not happen
    }
    /* First, check if the shortest path with current weights is less than target */
    dijkstra(source, n, getWeight);
    if (dist[destination] < target) {
        // Impossible to achieve target
        for (int i = 0; i < n; ++i) {
            free(adj[i]);
        }
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    /* Next, try to adjust -1 weights to reach target */
    for (int i = 0; i < edgesSize; ++i) {
        if (edges[i][2] == -1) {
            edges[i][2] = 1; // Temporarily set to 1
        }
    }
    dijkstra(source, n, getWeight);
    if (dist[destination] > target) {
        // Impossible to achieve target
        for (int i = 0; i < n; ++i) {
            free(adj[i]);
        }
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    /* Adjust -1 weights to reach target */
    for (int i = 0; i < edgesSize; ++i) {
        if (edges[i][2] == 1) {
            // Try increasing this edge weight
            int originalWeight = edges[i][2];
            edges[i][2] = target - dist[destination] + 1; // Increase weight
            dijkstra(source, n, getWeight);
            if (dist[destination] > target) {
                edges[i][2] = originalWeight; // Revert if overshoot
            } else if (dist[destination] == target) {
                break; // Found a valid configuration
            }
        }
    }
    /* Prepare return values */
    int** result = (int**)malloc(edgesSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(edgesSize * sizeof(int));
    for (int i = 0; i < edgesSize; ++i) {
        result[i] = (int*)malloc(3 * sizeof(int));
        result[i][0] = edges[i][0];
        result[i][1] = edges[i][1];
        result[i][2] = edges[i][2];
        (*returnColumnSizes)[i] = 3;
    }
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    *returnSize = edgesSize;
    return result;
}