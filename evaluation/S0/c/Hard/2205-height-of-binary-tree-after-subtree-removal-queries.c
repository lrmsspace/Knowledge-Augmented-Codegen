// Source: https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given the root of a binary tree with n nodes. Each node is assigned a unique value from 1 to n. You are also given an array queries of size m.
//
// You have to perform m independent queries on the tree where in the ith query you do the following:
//
//
// 	Remove the subtree rooted at the node with the value queries[i] from the tree. It is guaranteed that queries[i] will not be equal to the value of the root.
//
//
// Return an array answer of size m where answer[i] is the height of the tree after performing the ith query.
//
// Note:
//
//
// 	The queries are independent, so the tree returns to its initial state after each query.
// 	The height of a tree is the number of edges in the longest simple path from the root to some node in the tree.
//
// Example:
// Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
// Output: [2]
// Explanation: The diagram above shows the tree after removing the subtree rooted at node with value 4.
// The height of the tree is 2 (The path 1 -> 3 -> 2).
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= n
// 	All the values in the tree are unique.
// 	m == queries.length
// 	1 <= m <= min(n, 104)
// 	1 <= queries[i] <= n
// 	queries[i] != root.val
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
int* treeQueries(struct TreeNode* root, int* queries, int queriesSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    if (queriesSize <= 0) return NULL;

    /* Preprocessing: Compute depth and height of each node */
    int n = 0;
    void count_nodes(struct TreeNode *node) {
        if (!node) return;
        n++;
        count_nodes(node->left);
        count_nodes(node->right);
    }
    count_nodes(root);

    int *depth = (int*)malloc((n + 1) * sizeof(int));
    int *height = (int*)malloc((n + 1) * sizeof(int));
    if (!depth || !height) {
        free(depth); free(height);
        return NULL;
    }

    void compute_depth_height(struct TreeNode *node, int d) {
        if (!node) return;
        depth[node->val] = d;
        compute_depth_height(node->left, d + 1);
        compute_depth_height(node->right, d + 1);
        int hl = node->left ? height[node->left->val] + 1 : 0;
        int hr = node->right ? height[node->right->val] + 1 : 0;
        height[node->val] = hl > hr ? hl : hr;
    }
    compute_depth_height(root, 0);

    /* Preprocessing: Compute max heights at each depth */
    int maxDepth = 0;
    for (int i = 1; i <= n; ++i) {
        if (depth[i] > maxDepth) maxDepth = depth[i];
    }

    int *maxHeightAtDepth = (int*)calloc(maxDepth + 1, sizeof(int));
    if (!maxHeightAtDepth) {
        free(depth); free(height);
        return NULL;
    }

    for (int i = 1; i <= n; ++i) {
        int d = depth[i];
        if (height[i] > maxHeightAtDepth[d]) {
            maxHeightAtDepth[d] = height[i];
        }
    }

    /* Answer queries */
    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) {
        free(depth); free(height); free(maxHeightAtDepth);
        return NULL;
    }

    for (int i = 0; i < queriesSize; ++i) {
        int q = queries[i];
        int d = depth[q];
        int h = height[q];

        if (h < maxHeightAtDepth[d]) {
            results[i] = maxDepth;
        } else {
            results[i] = maxDepth - h - 1;
        }
    }
    free(depth);
    free(height);
    free(maxHeightAtDepth);
    return results;
}
