// Source: https://leetcode.com/problems/second-minimum-time-to-reach-destination/   |   Difficulty: Hard
//
// Problem Description:
// A city is represented as a bi-directional connected graph with n vertices where each vertex is labeled from 1 to n (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself. The time taken to traverse any edge is time minutes.
//
// Each vertex has a traffic signal which changes its color from green to red and vice versa every change minutes. All signals change at the same time. You can enter a vertex at any time, but can leave a vertex only when the signal is green. You cannot wait at a vertex if the signal is green.
//
// The second minimum value is defined as the smallest value strictly larger than the minimum value.
//
//
// 	For example the second minimum value of [2, 3, 4] is 3, and the second minimum value of [2, 2, 4] is 4.
//
//
// Given n, edges, time, and change, return the second minimum time it will take to go from vertex 1 to vertex n.
//
// Notes:
//
//
// 	You can go through any vertex any number of times, including 1 and n.
// 	You can assume that when the journey starts, all signals have just turned green.
//
// Example:
// Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
// Output: 13
// Explanation:
// The figure on the left shows the given graph.
// The blue path in the figure on the right is the minimum time path.
// The time taken is:
// - Start at 1, time elapsed=0
// - 1 -> 4: 3 minutes, time elapsed=3
// - 4 -> 5: 3 minutes, time elapsed=6
// Hence the minimum time needed is 6 minutes.
//
// The red path shows the path to get the second minimum time.
// - Start at 1, time elapsed=0
// - 1 -> 3: 3 minutes, time elapsed=3
// - 3 -> 4: 3 minutes, time elapsed=6
// - Wait at 4 for 4 minutes, time elapsed=10
// - 4 -> 5: 3 minutes, time elapsed=13
// Hence the second minimum time is 13 minutes.
//
// Constraints:
// 2 <= n <= 104
// 	n - 1 <= edges.length <= min(2 * 104, n * (n - 1) / 2)
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	There are no duplicate edges.
// 	Each vertex can be reached directly or indirectly from every other vertex.
// 	1 <= time, change <= 103
//
// Helpful references (internal KB):
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
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

int secondMinimum(int n, int** edges, int edgesSize, int* edgesColSize, int time, int change) {
	(void)edgesColSize;

	if (n <= 1) {
		return 0;
	}

	// Build the graph using an adjacency list representation
	int* head = (int*)malloc(n * sizeof(int));
	int* to = (int*)malloc(2 * edgesSize * sizeof(int));
	int* next = (int*)malloc(2 * edgesSize * sizeof(int));
	int* dist = (int*)malloc(n * sizeof(int));
	int* queue = (int*)malloc(n * sizeof(int));
	int idx = 0;
	int front = 0;
	int rear = 0;

	if (!head || !to || !next || !dist || !queue) {
		free(head);
		free(to);
		free(next);
		free(dist);
		free(queue);
		return -1;
	}

	for (int i = 0; i < n; ++i) {
		head[i] = -1;
		dist[i] = -1;
	}

	for (int i = 0; i < edgesSize; ++i) {
		int u = edges[i][0] - 1; // Convert to 0-based index
		int v = edges[i][1] - 1;

		to[idx] = v;
		next[idx] = head[u];
		head[u] = idx++;
		
		to[idx] = u;
		next[idx] = head[v];
		head[v] = idx++;
	}

	dist[0] = 0;
	queue[rear++] = 0;

	while (front < rear) {
		int u = queue[front++];
		
		for (int e = head[u]; e != -1; e = next[e]) {
			int v = to[e];
			if (dist[v] == -1) {
				dist[v] = dist[u] + time;
				queue[rear++] = v;
			} else if (dist[v] > dist[u]) {
				dist[v] = dist[u] + time;
			}
		}
	}

	int minTimeToN = dist[n - 1];
	if (minTimeToN == -1) {
		return -1; // No path from 1 to n
	}

	long long secondMinTimeToN = -1;

	for (int u = 0; u < n; ++u) {
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (dist[u] != -1 && dist[v] != -1) {
                long long timeToV = dist[u] + time;
                if (timeToV > dist[v]) {
                    timeToV = dist[v] + time;
                }
                if (timeToV > minTimeToN && (secondMinTimeToN == -1 || timeToV < secondMinTimeToN)) {
                    secondMinTimeToN = timeToV;
                }
            }
        }
    }
    

    free(head);
    free(to);
    free(next);
    free(dist);
    free(queue);

    return secondMinTimeToN;
}
