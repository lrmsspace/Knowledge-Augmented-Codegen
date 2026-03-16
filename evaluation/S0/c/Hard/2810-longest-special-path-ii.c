// Source: https://leetcode.com/problems/longest-special-path-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node in which all node values are distinct, except for at most one value that may appear twice.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,1],[1,2,3],[1,3,1],[2,4,6],[4,7,2],[3,5,2],[3,6,5],[6,8,3]], nums = [1,1,0,3,1,2,1,1,0]
//
// Output: [9,3]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums.
//
//
//
// The longest special paths are 1 -> 2 -> 4 and 1 -> 3 -> 6 -> 8, both having a length of 9. The minimum number of nodes across all longest special paths is 3.
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

    // Result array
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = 0; // max length
    result[1] = n + 1; // min nodes

    // DFS function
    void dfs(Node* node, Node* parent, int* countMap, int uniqueCount, int hasDuplicate, long long currentLength, int currentNodes) {
        countMap[nums[node->id]]++;
        if (countMap[nums[node->id]] == 1) {
            uniqueCount++;
        } else if (countMap[nums[node->id]] == 2) {
            hasDuplicate = 1;
        }

        if (uniqueCount + hasDuplicate > 2) {
            countMap[nums[node->id]]--;
            return;
        }

        if (currentLength > result[0]) {
            result[0] = currentLength;
            result[1] = currentNodes;
        } else if (currentLength == result[0] && currentNodes < result[1]) {
            result[1] = currentNodes;
        }
        for (int i = 0; i < node->edgeCount; i++) {
            Node* neighbor = node->edges[i].to;
            int length = node->edges[i].length;
            if (neighbor != parent) {
                dfs(neighbor, node, countMap, uniqueCount, hasDuplicate, currentLength + length, currentNodes + 1);
            }
        }
        countMap[nums[node->id]]--;
    }
    int* countMap = (int*)calloc(50001, sizeof(int));
    dfs(&nodes[0], NULL, countMap, 0, 0, 0, 1);
    free(countMap);
    for (int i = 0; i < n; i++) {
        free(nodes[i].edges);
    }
    free(nodes);
    *returnSize = 2;
    return result;
}
