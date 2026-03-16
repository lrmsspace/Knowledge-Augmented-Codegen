// Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
//
// You are also given an integer array nums of length n and an integer maxDiff.
//
// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
//
// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], find the minimum distance between nodes ui and vi. If no path exists between the two nodes, return -1 for that query.
//
// Return an array answer, where answer[i] is the result of the ith query.
//
// Note: The edges between the nodes are unweighted.
//
// Example:
// Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]
//
// Output: [1,1]
//
// Explanation:
//
// The resulting graph is:
//
//
//
//
// 	
// 		
// 			Query
// 			Shortest Path
// 			Minimum Distance
// 		
// 		
// 			[0, 3]
// 			0 → 3
// 			1
// 		
// 		
// 			[2, 4]
// 			2 → 4
// 			1
// 		
// 	
//
//
// Thus, the output is [1, 1].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
// 	0 <= maxDiff <= 105
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	0 <= ui, vi < n
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
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
int* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    
    // Build adjacency list based on maxDiff
    typedef struct Node {
        int val;
        struct Node* next;
    } Node;

    Node** graph = (Node**)calloc(n, sizeof(Node*));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (abs(nums[i] - nums[j]) <= maxDiff) {
                Node* node1 = (Node*)malloc(sizeof(Node));
                node1->val = j;
                node1->next = graph[i];
                graph[i] = node1;

                Node* node2 = (Node*)malloc(sizeof(Node));
                node2->val = i;
                node2->next = graph[j];
                graph[j] = node2;
            }
        }
    }

    // Prepare result array
    int* results = (int*)malloc(queriesSize * sizeof(int));

    // Process each query using BFS
    for (int q = 0; q < queriesSize; q++) {
        int start = queries[q][0];
        int end = queries[q][1];

        // BFS initialization
        int* queue = (int*)malloc(n * sizeof(int));
        int front = 0, back = 0;
        int* visited = (int*)calloc(n, sizeof(int));
        visited[start] = 1;
        queue[back++] = start;
        int found = 0;

        // BFS loop
        while (front < back) {
            int curr = queue[front++];
            if (curr == end) {
                found = 1;
                break;
            }
            Node* neighbor = graph[curr];
            while (neighbor) {
                if (!visited[neighbor->val]) {
                    visited[neighbor->val] = 1;
                    queue[back++] = neighbor->val;
                }
                neighbor = neighbor->next;
            }
        }

        results[q] = found ? 1 : -1;

        free(queue);
        free(visited);
    }

    // Free graph memory
    for (int i = 0; i < n; i++) {
        Node* curr = graph[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph);

    *returnSize = queriesSize;
    return results;
}