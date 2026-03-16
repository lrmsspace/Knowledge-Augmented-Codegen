// Source: https://leetcode.com/problems/minimum-time-to-transport-all-individuals/   |   Difficulty: Hard
//
// Problem Description:
// You are given n individuals at a base camp who need to cross a river to reach a destination using a single boat. The boat can carry at most k people at a time. The trip is affected by environmental conditions that vary cyclically over m stages.
//
// Each stage j has a speed multiplier mul[j]:
//
//
// 	If mul[j] > 1, the trip slows down.
// 	If mul[j] < 1, the trip speeds up.
//
//
// Each individual i has a rowing strength represented by time[i], the time (in minutes) it takes them to cross alone in neutral conditions.
//
// Rules:
//
//
// 	A group g departing at stage j takes time equal to the maximum time[i] among its members, multiplied by mul[j] minutes to reach the destination.
// 	After the group crosses the river in time d, the stage advances by floor(d) % m steps.
// 	If individuals are left behind, one person must return with the boat. Let r be the index of the returning person, the return takes time[r] × mul[current_stage], defined as return_time, and the stage advances by floor(return_time) % m.
//
//
// Return the minimum total time required to transport all individuals. If it is not possible to transport all individuals to the destination, return -1.
//
// Example:
// Input: n = 1, k = 1, m = 2, time = [5], mul = [1.0,1.3]
//
// Output: 5.00000
//
// Explanation:
//
//
// 	Individual 0 departs from stage 0, so crossing time = 5 × 1.00 = 5.00 minutes.
// 	All team members are now at the destination. Thus, the total time taken is 5.00 minutes.
//
// Constraints:
// 1 <= n == time.length <= 12
// 	1 <= k <= 5
// 	1 <= m <= 5
// 	1 <= time[i] <= 100
// 	m == mul.length
// 	0.5 <= mul[i] <= 2.0
//
// Helpful references (internal KB):
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, greedy, dijkstra, bellman-ford)
//   • When to use: This algorithm finds a minimum-cost flow of a given amount from a source to a sink in a flow network. It is suitable when both flow capacity and edge costs are present.
//   • Idea: The successive shortest path algorithm iteratively finds augmenting paths with minimum cost in a residual graph, using shortest path algorithms like Bellman-Ford or Dijkstra with potentials, until the desired flow is achieved. Its complexity depends on the shortest path algorithm used and the number of augmentations.
//   • Invariants: The total flow pushed from source to sink never exceeds the sum of capacities of edges leaving the source.; For any edge (u, v) with flow f_uv, 0 <= f_uv <= capacity_uv.
//   • Tips: Use potentials with Dijkstra for non-negative edge costs in the residual graph.; Bellman-Ford is necessary if initial edge costs can be negative or if potentials are not used.
//   • Pitfalls: Incorrectly updating potentials can lead to wrong shortest paths.; Forgetting to add reverse edges with negative costs in the residual graph.
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double minTime(int n, int k, int m, int* time, int timeSize, double* mul, int mulSize) {
    int maxState = 1 << n;
    double dp[maxState][m];
    for (int i = 0; i < maxState; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = 1e9;
        }
    }
    dp[0][0] = 0.0;

    for (int state = 0; state < maxState; ++state) {
        for (int stage = 0; stage < m; ++stage) {
            if (dp[state][stage] >= 1e9) continue;

            // Generate all subsets of size <= k from remaining individuals
            for (int sub = state ^ (maxState - 1); sub > 0; sub = (sub - 1) & (state ^ (maxState - 1))) {
                if (__builtin_popcount(sub) > k) continue;

                // Calculate crossing time
                int maxTime = 0;
                for (int i = 0; i < n; ++i) {
                    if (sub & (1 << i)) {
                        if (time[i] > maxTime) {
                            maxTime = time[i];
                        }
                    }
                }
                double crossTime = maxTime * mul[stage];
                int nextStage = (stage + (int)crossTime) % m;
                int nextState = state | sub;

                // If all individuals have crossed, update dp without return trip
                if (nextState == maxState - 1) {
                    if (dp[nextState][nextStage] > dp[state][stage] + crossTime) {
                        dp[nextState][nextStage] = dp[state][stage] + crossTime;
                    }
                    continue;
                }

                // Consider return trips
                for (int ret = 0; ret < n; ++ret) {
                    if (!(nextState & (1 << ret))) continue;

                    double returnTime = time[ret] * mul[nextStage];
                    int finalStage = (nextStage + (int)returnTime) % m;

                    if (dp[state | sub][finalStage] > dp[state][stage] + crossTime + returnTime) {
                        dp[state | sub][finalStage] = dp[state][stage] + crossTime + returnTime;
                    }
                }
            }
        }
    }       
    double result = 1e9;
    for (int stage = 0; stage < m; ++stage) {
        if (dp[maxState - 1][stage] < result) {
            result = dp[maxState - 1][stage];
        }
    }
    return (result >= 1e9) ? -1.0 : result;
}
