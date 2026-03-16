// Source: https://leetcode.com/problems/parallel-courses-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given a 2D integer array relations where relations[j] = [prevCoursej, nextCoursej] denotes that course prevCoursej has to be completed before course nextCoursej (prerequisite relationship). Furthermore, you are given a 0-indexed integer array time where time[i] denotes how many months it takes to complete the (i+1)th course.
//
// You must find the minimum number of months needed to complete all the courses following these rules:
//
//
// 	You may start taking a course at any time if the prerequisites are met.
// 	Any number of courses can be taken at the same time.
//
//
// Return the minimum number of months needed to complete all the courses.
//
// Note: The test cases are generated such that it is possible to complete every course (i.e., the graph is a directed acyclic graph).
//
// Example:
// Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
// Output: 8
// Explanation: The figure above represents the given graph and the time required to complete each course. 
// We start course 1 and course 2 simultaneously at month 0.
// Course 1 takes 3 months and course 2 takes 2 months to complete respectively.
// Thus, the earliest time we can start course 3 is at month 3, and the total time required is 3 + 5 = 8 months.
//
// Constraints:
// 1 <= n <= 5 * 104
// 	0 <= relations.length <= min(n * (n - 1) / 2, 5 * 104)
// 	relations[j].length == 2
// 	1 <= prevCoursej, nextCoursej <= n
// 	prevCoursej != nextCoursej
// 	All the pairs [prevCoursej, nextCoursej] are unique.
// 	time.length == n
// 	1 <= time[i] <= 104
// 	The given graph is a directed acyclic graph.
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Shortest Paths (graph, topo, dp-1d)
//   • When to use: This algorithm finds the shortest paths from a single source vertex to all other vertices in a directed acyclic graph (DAG) with arbitrary edge weights.
//   • Idea: This algorithm computes single-source shortest paths in a Directed Acyclic Graph (DAG) by processing vertices in topological order, relaxing outgoing edges. It achieves a time complexity of O(V + E).
//   • Invariants: The distance to the source vertex, distTo[s], remains 0 throughout the algorithm.; For any vertex v, distTo[v] always stores the shortest path found so far from s to v.
//   • Tips: First, perform a topological sort on the DAG to determine the processing order.; Initialize all distances to infinity, except the source vertex which is zero.
//   • Pitfalls: Applying this algorithm to a graph containing cycles will yield incorrect results.; An incorrect topological sort order will lead to incorrect shortest path calculations.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumTime(int n, int** relations, int relationsSize, int* relationsColSize, int* time, int timeSize) {
    // Adjacency list and in-degree array
    int **adj = (int**)calloc(n, sizeof(int*));
    int *inDegree = (int*)calloc(n, sizeof(int));
    int *adjColSize = (int*)calloc(n, sizeof(int));

    // Build the graph
    for (int i = 0; i < relationsSize; i++) {
        int u = relations[i][0] - 1;
        int v = relations[i][1] - 1;
        adj[u] = (int*)realloc(adj[u], (adjColSize[u] + 1) * sizeof(int));
        adj[u][adjColSize[u]++] = v;
        inDegree[v]++;
    }

    // Queue for topological sort
    int *queue = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;

    // Initialize queue with nodes of in-degree 0
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            queue[back++] = i;
        }
    }

    // Array to store the earliest completion time for each course
    int *earliestCompletion = (int*)calloc(n, sizeof(int));

    // Topological sort and calculate earliest completion times
    while (front < back) {
        int u = queue[front++];
        earliestCompletion[u] += time[u];

        for (int i = 0; i < adjColSize[u]; i++) {
            int v = adj[u][i];
            if (earliestCompletion[v] < earliestCompletion[u]) {
                earliestCompletion[v] = earliestCompletion[u];
            }
            inDegree[v]--;
            if (inDegree[v] == 0) {
                queue[back++] = v;
            }
        }
    }

    // Find the maximum completion time
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (earliestCompletion[i] > result) {
            result = earliestCompletion[i];
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(inDegree);
    free(adjColSize);
    free(queue);
    free(earliestCompletion);       
    return result;
}
