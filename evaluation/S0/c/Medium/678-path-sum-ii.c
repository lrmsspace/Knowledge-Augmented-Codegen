// Source: https://leetcode.com/problems/path-sum-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum. Each path should be returned as a list of the node values, not node references.
//
// A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.
//
// Example:
// Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
// Output: [[5,4,11,2],[5,8,4,5]]
// Explanation: There are two paths whose sum equals targetSum:
// 5 + 4 + 11 + 2 = 22
// 5 + 8 + 4 + 5 = 22
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5000].
// 	-1000 <= Node.val <= 1000
// 	-1000 <= targetSum <= 1000
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
int** pathSum(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes) {
    int** result = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;
    
    if (!root) {
        return result;
    }
    
    int path[5000];
    int pathLen = 0;
    
    void dfs(struct TreeNode* node, int currentSum) {
        if (!node) {
            return;
        }
        
        path[pathLen++] = node->val;
        currentSum += node->val;
        
        if (!node->left && !node->right) {
            if (currentSum == targetSum) {
                result = realloc(result, sizeof(int*) * (*returnSize + 1));
                (*returnColumnSizes) = realloc(*returnColumnSizes, sizeof(int) * (*returnSize + 1));
                
                result[*returnSize] = malloc(sizeof(int) * pathLen);
                memcpy(result[*returnSize], path, sizeof(int) * pathLen);
                (*returnColumnSizes)[*returnSize] = pathLen;
                (*returnSize)++;
            }
        } else {
            dfs(node->left, currentSum);
            dfs(node->right, currentSum);
        }
        
        pathLen--;
    }
    
    dfs(root, 0);
    
    return result;      
}
