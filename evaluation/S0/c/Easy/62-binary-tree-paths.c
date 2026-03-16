// Source: https://leetcode.com/problems/binary-tree-paths/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return all root-to-leaf paths in any order.
//
// A leaf is a node with no children.
//
// Example:
// Input: root = [1,2,3,null,5]
// Output: ["1->2->5","1->3"]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	-100 <= Node.val <= 100
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
char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    char** paths = NULL;
    *returnSize = 0;
    
    if (!root) {
        return paths;
    }
    
    // Helper function to perform DFS and build paths
    void dfs(struct TreeNode* node, char* path, int pathLen) {
        if (!node) {
            return;
        }
        
        // Append current node's value to the path
        int len = snprintf(path + pathLen, 12, "%d", node->val);
        pathLen += len;
        
        // If it's a leaf node, add the path to the result
        if (!node->left && !node->right) {
            paths = realloc(paths, sizeof(char*) * (*returnSize + 1));
            paths[*returnSize] = malloc(pathLen + 1);
            strcpy(paths[*returnSize], path);
            (*returnSize)++;
        } else {
            // Continue DFS on left and right children
            if (node->left) {
                path[pathLen++] = '-';
                path[pathLen++] = '>';
                dfs(node->left, path, pathLen);
                pathLen -= 2; // backtrack
            }
            if (node->right) {
                path[pathLen++] = '-';
                path[pathLen++] = '>';
                dfs(node->right, path, pathLen);
                pathLen -= 2; // backtrack
            }
        }
    }
    
    char path[100]; // Buffer to hold the current path
    dfs(root, path, 0);
    
    return paths;       
}
