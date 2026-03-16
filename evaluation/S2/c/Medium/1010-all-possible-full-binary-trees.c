// Source: https://leetcode.com/problems/all-possible-full-binary-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.
//
// Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.
//
// A full binary tree is a binary tree where each node has exactly 0 or 2 children.
//
// Example:
// Input: n = 7
// Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
//
// Constraints:
// 1 <= n <= 20
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

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
struct TreeNode** allPossibleFBT(int n, int* returnSize) {
    // Base case: If n is even, return an empty array since full binary trees cannot have an even number of nodes.
    if (n % 2 == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // Base case: If n is 1, return an array with a single node.
    if (n == 1) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = 0;
        node->left = NULL;
        node->right = NULL;
        
        struct TreeNode** result = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
        result[0] = node;
        *returnSize = 1;
        return result;
    }
    
    // Recursive case: Generate all full binary trees for left and right subtrees.
    int totalTrees = 0;
    struct TreeNode** result = NULL;

    for (int leftNodes = 1; leftNodes < n; leftNodes += 2) {
        int rightNodes = n - 1 - leftNodes; // Subtract the root node
        
        int leftSize, rightSize;
        struct TreeNode** leftTrees = allPossibleFBT(leftNodes, &leftSize);
        struct TreeNode** rightTrees = allPossibleFBT(rightNodes, &rightSize);
        
        // Combine left and right subtrees with a new root node
        for (int i = 0; i < leftSize; i++) {
            for (int j = 0; j < rightSize; j++) {
                struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                root->val = 0;
                root->left = leftTrees[i];
                root->right = rightTrees[j];
                
                totalTrees++;
                result = (struct TreeNode**)realloc(result, totalTrees * sizeof(struct TreeNode*));
                result[totalTrees - 1] = root;
            }
        }
        
        free(leftTrees);
        free(rightTrees);
    }
    
    *returnSize = totalTrees;
    return result;      
}
