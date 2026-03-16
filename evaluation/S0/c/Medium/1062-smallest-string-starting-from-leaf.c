// Source: https://leetcode.com/problems/smallest-string-starting-from-leaf/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree where each node has a value in the range [0, 25] representing the letters 'a' to 'z'.
//
// Return the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
//
// As a reminder, any shorter prefix of a string is lexicographically smaller.
//
//
// 	For example, "ab" is lexicographically smaller than "aba".
//
//
// A leaf of a node is a node that has no children.
//
// Example:
// Input: root = [0,1,2,3,4,3,4]
// Output: "dba"
//
// Constraints:
// The number of nodes in the tree is in the range [1, 8500].
// 	0 <= Node.val <= 25
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
char* smallestFromLeaf(struct TreeNode* root) {
    if (!root) return "";

    #define MAX_DEPTH 8500
    char path[MAX_DEPTH + 1];
    char* result = NULL;
    int path_len = 0;

    void dfs(struct TreeNode* node) {
        if (!node) return;

        path[path_len++] = 'a' + node->val;

        if (!node->left && !node->right) {
            path[path_len] = '\0';
            // Reverse the path to get leaf-to-root string
            for (int i = 0; i < path_len / 2; ++i) {
                char temp = path[i];
                path[i] = path[path_len - 1 - i];
                path[path_len - 1 - i] = temp;
            }

            if (!result || strcmp(path, result) < 0) {
                free(result);
                result = strdup(path);
            }

            // Reverse back to original for further traversal
            for (int i = 0; i < path_len / 2; ++i) {
                char temp = path[i];
                path[i] = path[path_len - 1 - i];
                path[path_len - 1 - i] = temp;
            }
        } else {
            dfs(node->left);
            dfs(node->right);
        }

        --path_len;
    }

    dfs(root);
    return result;      
}
