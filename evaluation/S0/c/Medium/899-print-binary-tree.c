// Source: https://leetcode.com/problems/print-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, construct a 0-indexed m x n string matrix res that represents a formatted layout of the tree. The formatted layout matrix should be constructed using the following rules:
//
//
// 	The height of the tree is height and the number of rows m should be equal to height + 1.
// 	The number of columns n should be equal to 2height+1 - 1.
// 	Place the root node in the middle of the top row (more formally, at location res[0][(n-1)/2]).
// 	For each node that has been placed in the matrix at position res[r][c], place its left child at res[r+1][c-2height-r-1] and its right child at res[r+1][c+2height-r-1].
// 	Continue this process until all the nodes in the tree have been placed.
// 	Any empty cells should contain the empty string "".
//
//
// Return the constructed matrix res.
//
// Example:
// Input: root = [1,2]
// Output: 
// [["","1",""],
//  ["2","",""]]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 210].
// 	-99 <= Node.val <= 99
// 	The depth of the tree will be in the range [1, 10].
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** printTree(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int height = 0;
    void getHeight(struct TreeNode* node, int h) {
        if (!node) return;
        if (h > height) height = h;
        getHeight(node->left, h + 1);
        getHeight(node->right, h + 1);
    }
    getHeight(root, 0);
    
    int m = height + 1;
    int n = (1 << (height + 1)) - 1; // 2^(height+1) - 1
    
    char*** res = (char***)malloc(m * sizeof(char**));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        res[i] = (char**)malloc(n * sizeof(char*));
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            res[i][j] = "";
        }
    }
    
    void fill(struct TreeNode* node, int r, int c, int h) {
        if (!node) return;
        char buffer[12];
        sprintf(buffer, "%d", node->val);
        res[r][c] = strdup(buffer);
        fill(node->left, r + 1, c - (1 << (h - r - 1)), h);
        fill(node->right, r + 1, c + (1 << (h - r - 1)), h);
    }
    fill(root, 0, (n - 1) / 2, height);
    
    *returnSize = m;
    return res;     
}
