// Source: https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.
//
// Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.
//
// Note that you need to maximize the answer before taking the mod and not after taking it.
//
// Example:
// Input: root = [1,2,3,4,5,6]
// Output: 110
// Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
//
// Constraints:
// The number of nodes in the tree is in the range [2, 5 * 104].
// 	1 <= Node.val <= 104
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxProduct(struct TreeNode* root) {
    long long MOD = 1e9 + 7;
    long long totalSum = 0;
    long long maxProd = 0;

    // Helper function to calculate total sum of the tree
    long long calculateTotalSum(struct TreeNode* node) {
        if (!node) return 0;
        return node->val + calculateTotalSum(node->left) + calculateTotalSum(node->right);
    }

    // Helper function to find maximum product
    long long findMaxProduct(struct TreeNode* node) {
        if (!node) return 0;
        long long subTreeSum = node->val + findMaxProduct(node->left) + findMaxProduct(node->right);
        long long product = subTreeSum * (totalSum - subTreeSum);
        if (product > maxProd) {
            maxProd = product;
        }
        return subTreeSum;
    }

    totalSum = calculateTotalSum(root);
    findMaxProduct(root);

    return maxProd % MOD;       
}
