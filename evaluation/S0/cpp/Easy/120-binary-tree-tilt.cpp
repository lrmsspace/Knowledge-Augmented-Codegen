// Source: https://leetcode.com/problems/binary-tree-tilt/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the sum of every tree node's tilt.
//
// The tilt of a tree node is the absolute difference between the sum of all left subtree node values and all right subtree node values. If a node does not have a left child, then the sum of the left subtree node values is treated as 0. The rule is similar if the node does not have a right child.
//
// Example:
// Input: root = [1,2,3]
// Output: 1
// Explanation: 
// Tilt of node 2 : |0-0| = 0 (no children)
// Tilt of node 3 : |0-0| = 0 (no children)
// Tilt of node 1 : |2-3| = 1 (left subtree is just left child, so sum is 2; right subtree is just right child, so sum is 3)
// Sum of every tilt : 0 + 0 + 1 = 1
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	-1000 <= Node.val <= 1000
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
    int findTilt(TreeNode* root) {
        int totalTilt = 0;

        std::function<int(TreeNode*)> computeSumAndTilt = [&](TreeNode* node) -> int {
            if (!node) return 0;

            int leftSum = computeSumAndTilt(node->left);
            int rightSum = computeSumAndTilt(node->right);

            int nodeTilt = std::abs(leftSum - rightSum);
            totalTilt += nodeTilt;

            return leftSum + rightSum + node->val;
        };

        computeSumAndTilt(root);
        return totalTilt;           
    }
};
