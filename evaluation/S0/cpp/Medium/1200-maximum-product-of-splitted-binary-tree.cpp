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
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxProduct(TreeNode* root) {
        const int MOD = 1e9 + 7;
        long long totalSum = computeTotalSum(root);
        long long maxProd = 0;

        function<long long(TreeNode*)> dfs = [&](TreeNode* node) -> long long {
            if (!node) return 0;
            long long leftSum = dfs(node->left);
            long long rightSum = dfs(node->right);
            long long currSum = leftSum + rightSum + node->val;

            // Calculate product of the two subtrees
            long long product = currSum * (totalSum - currSum);
            maxProd = max(maxProd, product);

            return currSum;
        };

        dfs(root);
        return maxProd % MOD;           
    }
};
