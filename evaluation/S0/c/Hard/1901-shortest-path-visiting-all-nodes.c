// Source: https://leetcode.com/problems/shortest-path-visiting-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
//
// Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
//
// Example:
// Input: graph = [[1,2,3],[0],[0],[0]]
// Output: 4
// Explanation: One possible path is [1,0,2,0,3]
//
// Constraints:
// n == graph.length
// 	1 <= n <= 12
// 	0 <= graph[i].length < n
// 	graph[i] does not contain i.
// 	If graph[a] contains b, then graph[b] contains a.
// 	The input graph is always connected.
//

int shortestPathLength(int** graph, int graphSize, int* graphColSize) {
    if (graphSize <= 1) return 0;

    const int FULL_MASK = (1 << graphSize) - 1;
    typedef struct {
        int node;
        int mask;
    } State;

    State queue[graphSize * FULL_MASK];
    int visited[graphSize][FULL_MASK];
    memset(visited, 0, sizeof(visited));

    int front = 0, back = 0;
    for (int i = 0; i < graphSize; ++i) {
        State init = {i, 1 << i};
        queue[back++] = init;
        visited[i][1 << i] = 1;
    }

    int steps = 0;
    while (front < back) {
        int size = back - front;
        for (int i = 0; i < size; ++i) {
            State curr = queue[front++];
            if (curr.mask == FULL_MASK) return steps;

            for (int j = 0; j < graphColSize[curr.node]; ++j) {
                int neighbor = graph[curr.node][j];
                int nextMask = curr.mask | (1 << neighbor);
                if (!visited[neighbor][nextMask]) {
                    visited[neighbor][nextMask] = 1;
                    State nextState = {neighbor, nextMask};
                    queue[back++] = nextState;
                }
            }
        }
        steps++;
    }

    return -1; /* should not reach here */      
}
