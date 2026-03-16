// Source: https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/   |   Difficulty: Hard
//
// Problem Description:
// There is a country of n cities numbered from 0 to n - 1 where all the cities are connected by bi-directional roads. The roads are represented as a 2D integer array edges where edges[i] = [xi, yi, timei] denotes a road between cities xi and yi that takes timei minutes to travel. There may be multiple roads of differing travel times connecting the same two cities, but no road connects a city to itself.
//
// Each time you pass through a city, you must pay a passing fee. This is represented as a 0-indexed integer array passingFees of length n where passingFees[j] is the amount of dollars you must pay when you pass through city j.
//
// In the beginning, you are at city 0 and want to reach city n - 1 in maxTime minutes or less. The cost of your journey is the summation of passing fees for each city that you passed through at some moment of your journey (including the source and destination cities).
//
// Given maxTime, edges, and passingFees, return the minimum cost to complete your journey, or -1 if you cannot complete it within maxTime minutes.
//
// Example:
// Input: maxTime = 30, edges = [[0,1,10],[1,2,10],[2,5,10],[0,3,1],[3,4,10],[4,5,15]], passingFees = [5,1,2,20,20,3]
// Output: 11
// Explanation: The path to take is 0 -> 1 -> 2 -> 5, which takes 30 minutes and has $11 worth of passing fees.
//
// Constraints:
// 1 <= maxTime <= 1000
// 	n == passingFees.length
// 	2 <= n <= 1000
// 	n - 1 <= edges.length <= 1000
// 	0 <= xi, yi <= n - 1
// 	1 <= timei <= 1000
// 	1 <= passingFees[j] <= 1000 
// 	The graph may contain multiple edges between two nodes.
// 	The graph does not contain self loops.
//
// Helpful references (internal KB):
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minCost(int maxTime, int** edges, int edgesSize, int* edgesColSize, int* passingFees, int passingFeesSize) {
    typedef struct {
        int node;
        int time;
        int cost;
    } State;

    #define MAX_N 1000
    #define INF 0x3f3f3f3f

    // Adjacency list representation
    typedef struct Edge {
        int to;
        int time;
        struct Edge* next;
    } Edge;

    Edge* graph[MAX_N] = {0};

    // Build the graph
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int t = edges[i][2];

        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = v; e1->time = t; e1->next = graph[u]; graph[u] = e1;

        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = u; e2->time = t; e2->next = graph[v]; graph[v] = e2;
    }

    // Min-heap priority queue
    #define HEAP_SIZE 200000
    State heap[HEAP_SIZE];
    int heapSize = 0;

    void push(State s) {
        heap[heapSize++] = s;
        int i = heapSize - 1;
        while (i > 0) {
            int p = (i - 1) / 2;
            if (heap[p].cost <= heap[i].cost) break;
            State tmp = heap[p]; heap[p] = heap[i]; heap[i] = tmp;
            i = p;
        }
    }

    State pop() {
        State ret = heap[0];
        heap[0] = heap[--heapSize];
        int i = 0;
        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < heapSize && heap[left].cost < heap[smallest].cost) smallest = left;
            if (right < heapSize && heap[right].cost < heap[smallest].cost) smallest = right;
            if (smallest == i) break;
            State tmp = heap[i]; heap[i] = heap[smallest]; heap[smallest] = tmp;
            i = smallest;
        }
        return ret;
    }
    int dist[MAX_N][1001];
    for (int i = 0; i < passingFeesSize; i++) {
        for (int j = 0; j <= maxTime; j++) {
            dist[i][j] = INF;
        }
    }
    dist[0][0] = passingFees[0];
    push((State){0, 0, passingFees[0]});
    int result = -1;
    while (heapSize > 0) {
        State curr = pop();
        int u = curr.node;
        int timeSpent = curr.time;
        int costSoFar = curr.cost;

        if (u == passingFeesSize - 1) {
            result = costSoFar;
            break;
        }

        if (costSoFar > dist[u][timeSpent]) continue;

        for (Edge* e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;
            int t = e->time;
            int newTime = timeSpent + t;
            if (newTime <= maxTime) {
                int newCost = costSoFar + passingFees[v];
                if (newCost < dist[v][newTime]) {
                    dist[v][newTime] = newCost;
                    push((State){v, newTime, newCost});
                }
            }
        }
    }
    // Cleanup
    for (int i = 0; i < passingFeesSize; i++) {
        Edge* e = graph[i];
        while (e) {
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return result;       
}
