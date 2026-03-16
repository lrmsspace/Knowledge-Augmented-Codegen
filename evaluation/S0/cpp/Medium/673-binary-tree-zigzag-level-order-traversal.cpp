// Source: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[20,9],[15,7]]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 2000].
// 	-100 <= Node.val <= 100
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        bool leftToRight = true;

        while (!nodeQueue.empty()) {
            int levelSize = nodeQueue.size();
            vector<int> currentLevel(levelSize);

            for (int i = 0; i < levelSize; ++i) {
                TreeNode* currentNode = nodeQueue.front();
                nodeQueue.pop();

                // Determine the position to fill the current node's value
                int index = leftToRight ? i : (levelSize - 1 - i);
                currentLevel[index] = currentNode->val;

                // Add child nodes to the queue
                if (currentNode->left) {
                    nodeQueue.push(currentNode->left);
                }
                if (currentNode->right) {
                    nodeQueue.push(currentNode->right);
                }
            }

            // After finishing the level, flip the direction
            leftToRight = !leftToRight;
            result.push_back(currentLevel);
        }

        return result;          
    }
};
