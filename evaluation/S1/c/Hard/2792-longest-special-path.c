// Source: https://leetcode.com/problems/longest-special-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1, represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node such that all the values of the nodes in that path are unique.
//
// Note that a path may start and end at the same node.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums = [2,1,2,1,3,1]
//
// Output: [6,2]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums
//
//
//
// The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length of 6. The minimum number of nodes across all longest special paths is 2.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= lengthi <= 103
// 	nums.length == n
// 	0 <= nums[i] <= 5 * 104
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Depth-first search (graph, array, dfs, biconnected-components)
//   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
//   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
//   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
//   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
// - Strong Orientation (graph, tree, dfs)
//   • When to use: Use this when you need to convert an undirected, bridgeless, and connected graph into a strongly connected directed graph, ensuring reachability between any two vertices.
//   • Idea: This algorithm transforms a bridgeless, connected undirected graph into a strongly connected directed graph by performing a Depth-First Search. It orients DFS tree edges away from the root and back edges towards ancestors, achieving strong connectivity in O(V+E) time.
//   • Invariants: All DFS tree edges discovered so far are oriented from parent to child.; All back edges discovered so far are oriented from child to ancestor.
//   • Tips: Verify the input graph is connected and bridgeless before applying the algorithm.; During DFS, mark visited vertices and track parent-child relationships to distinguish edge types.
//   • Pitfalls: Applying to a graph with bridges will result in a non-strongly connected graph.; Incorrectly identifying or orienting back edges can break the strong connectivity property.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
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
int* longestSpecialPath(int** edges, int edgesSize, int* edgesColSize, int* nums, int numsSize, int* returnSize) {
    // Build adjacency list
    typedef struct Edge {
        int to;
        int length;
        struct Edge* next;
    } Edge;

    Edge* adj[50000];
    memset(adj, 0, sizeof(adj));

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1], length = edges[i][2];
        Edge* edgeU = (Edge*)malloc(sizeof(Edge));
        edgeU->to = v;
        edgeU->length = length;
        edgeU->next = adj[u];
        adj[u] = edgeU;

        Edge* edgeV = (Edge*)malloc(sizeof(Edge));
        edgeV->to = u;
        edgeV->length = length;
        edgeV->next = adj[v];
        adj[v] = edgeV;
    }

    // DFS to find longest special path
    int maxLength = 0;
    int minNodes = 0;

    void dfs(int node, int parent, int currentLength, int currentNodes, int* visited) {
        visited[nums[node]] = 1;

        if (currentLength > maxLength || (currentLength == maxLength && currentNodes < minNodes)) {
            maxLength = currentLength;
            minNodes = currentNodes;
        }

        for (Edge* edge = adj[node]; edge != NULL; edge = edge->next) {
            int nextNode = edge->to;
            if (nextNode != parent && !visited[nums[nextNode]]) {
                dfs(nextNode, node, currentLength + edge->length, currentNodes + 1, visited);
            }
        }

        visited[nums[node]] = 0;
    }

    int* visited = (int*)calloc(50001, sizeof(int));
    dfs(0, -1, 0, 1, visited);
    free(visited);

    // Free adjacency list
    for (int i = 0; i < numsSize; ++i) {
        Edge* edge = adj[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }

    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = maxLength;
    result[1] = minNodes;
    *returnSize =2;
    return result;
}
