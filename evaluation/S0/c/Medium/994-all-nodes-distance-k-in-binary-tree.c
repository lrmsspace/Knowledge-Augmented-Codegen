// Source: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
//
// You can return the answer in any order.
//
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
// Output: [7,4,1]
// Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 500].
// 	0 <= Node.val <= 500
// 	All the values Node.val are unique.
// 	target is the value of one of the nodes in the tree.
// 	0 <= k <= 1000
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distanceK(struct TreeNode* root, struct TreeNode* target, int k, int* returnSize) {
    #define MAXN 500
    #define MAXE 1000

    typedef struct Edge {
        int to;
        struct Edge* next;
    } Edge;

    Edge* graph[MAXN] = {0};
    int nodeCount = 0;

    // Build the graph from the binary tree
    void buildGraph(struct TreeNode* node, struct TreeNode* parent) {
        if (!node) return;
        int u = node->val;
        if (parent) {
            int v = parent->val;
            Edge* edgeU = (Edge*)malloc(sizeof(Edge));
            edgeU->to = v;
            edgeU->next = graph[u];
            graph[u] = edgeU;

            Edge* edgeV = (Edge*)malloc(sizeof(Edge));
            edgeV->to = u;
            edgeV->next = graph[v];
            graph[v] = edgeV;
        }
        buildGraph(node->left, node);
        buildGraph(node->right, node);
    }

    buildGraph(root, NULL);

    // BFS to find nodes at distance k
    int visited[MAXN] = {0};
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = target->val;
    visited[target->val] = 1;
    int currentDistance = 0;

    while (front < rear) {
        int size = rear - front;
        if (currentDistance == k) break;
        for (int i = 0; i < size; i++) {
            int u = queue[front++];
            Edge* edge = graph[u];
            while (edge) {
                int v = edge->to;
                if (!visited[v]) {
                    visited[v] = 1;
                    queue[rear++] = v;
                }
                edge = edge->next;
            }
        }
        currentDistance++;
    }

    // Collect results
    *returnSize = rear - front;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        result[i] = queue[front + i];
    }

    // Free graph memory
    for (int i = 0; i < MAXN; i++) {
        Edge* edge = graph[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    return result;
}
