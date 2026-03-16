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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* longestSpecialPath(int** edges, int edgesSize, int* edgesColSize, int* nums, int numsSize, int* returnSize) {
    int n = numsSize;

    // Build adjacency list
    typedef struct Node {
        int id;
        struct Edge* edges;
        int edgeCount;
    } Node;

    typedef struct Edge {
        Node* to;
        int length;
    } Edge;

    Node* nodes = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        nodes[i].id = i;
        nodes[i].edges = NULL;
        nodes[i].edgeCount = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int length = edges[i][2];

        nodes[u].edges = (Edge*)realloc(nodes[u].edges, (nodes[u].edgeCount + 1) * sizeof(Edge));
        nodes[u].edges[nodes[u].edgeCount].to = &nodes[v];
        nodes[u].edges[nodes[u].edgeCount].length = length;
        nodes[u].edgeCount++;

        nodes[v].edges = (Edge*)realloc(nodes[v].edges, (nodes[v].edgeCount + 1) * sizeof(Edge));
        nodes[v].edges[nodes[v].edgeCount].to = &nodes[u];
        nodes[v].edges[nodes[v].edgeCount].length = length;
        nodes[v].edgeCount++;
    }

    // DFS to find longest special path
    int maxLength = 0;
    int minNodes = n + 1;

    void dfs(Node* node, Node* parent, int currentLength, int currentNodes, int* visited) {
        visited[nums[node->id]]++;
        if (currentLength > maxLength || (currentLength == maxLength && currentNodes < minNodes)) {
            maxLength = currentLength;
            minNodes = currentNodes;
        }

        for (int i = 0; i < node->edgeCount; i++) {
            Node* neighbor = node->edges[i].to;
            int length = node->edges[i].length;
            if (neighbor != parent && visited[nums[neighbor->id]] == 0) {
                dfs(neighbor, node, currentLength + length, currentNodes + 1, visited);
            }
        }

        visited[nums[node->id]]--;
    }
    int* visited = (int*)calloc(50001, sizeof(int));
    dfs(&nodes[0], NULL, 0, 1, visited);
    free(visited);
    for (int i = 0; i < n; i++) {
        free(nodes[i].edges);
    }
    free(nodes);
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = maxLength;
    result[1] = minNodes;
    *returnSize = 2;
    return result;
}
