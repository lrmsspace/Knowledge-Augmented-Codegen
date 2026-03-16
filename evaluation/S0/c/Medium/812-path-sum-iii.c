// Source: https://leetcode.com/problems/path-sum-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.
//
// The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).
//
// Example:
// Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
// Output: 3
// Explanation: The paths that sum to 8 are shown.
//
// Constraints:
// The number of nodes in the tree is in the range [0, 1000].
// 	-109 <= Node.val <= 109
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
int pathSum(struct TreeNode* root, int targetSum) {
    if (!root) return 0;

    int count = 0;

    // Helper function to count paths with a given sum starting from the current node
    void dfs(struct TreeNode* node, long currSum) {
        if (!node) return;

        currSum += node->val;
        if (currSum == targetSum) {
            count++;
        }

        dfs(node->left, currSum);
        dfs(node->right, currSum);
    }

    // Start DFS from the current root
    dfs(root, 0);

    // Recur for left and right subtrees
    count += pathSum(root->left, targetSum);
    count += pathSum(root->right, targetSum);

    return count;       
}
