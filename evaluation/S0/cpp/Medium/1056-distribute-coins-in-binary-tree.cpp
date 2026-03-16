// Source: https://leetcode.com/problems/distribute-coins-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes where each node in the tree has node.val coins. There are n coins in total throughout the whole tree.
//
// In one move, we may choose two adjacent nodes and move one coin from one node to another. A move may be from parent to child, or from child to parent.
//
// Return the minimum number of moves required to make every node have exactly one coin.
//
// Example:
// Input: root = [3,0,0]
// Output: 2
// Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.
//
// Constraints:
// The number of nodes in the tree is n.
// 	1 <= n <= 100
// 	0 <= Node.val <= n
// 	The sum of all Node.val is n.
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
    int distributeCoins(TreeNode* root) {
        int moves = 0;

        function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
            if (!node) return 0;

            int leftBalance = dfs(node->left);
            int rightBalance = dfs(node->right);

            moves += abs(leftBalance) + abs(rightBalance);

            return node->val + leftBalance + rightBalance - 1;
        };

        dfs(root);
        return moves;           
    }
};
