// Source: https://leetcode.com/problems/cousins-in-binary-tree-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.
//
// Two nodes of a binary tree are cousins if they have the same depth with different parents.
//
// Return the root of the modified tree.
//
// Note that the depth of a node is the number of edges in the path from the root node to it.
//
// Example:
// Input: root = [5,4,9,1,10,null,7]
// Output: [0,0,0,7,7,null,11]
// Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
// - Node with value 5 does not have any cousins so its sum is 0.
// - Node with value 4 does not have any cousins so its sum is 0.
// - Node with value 9 does not have any cousins so its sum is 0.
// - Node with value 1 has a cousin with value 7 so its sum is 7.
// - Node with value 10 has a cousin with value 7 so its sum is 7.
// - Node with value 7 has cousins with values 1 and 10 so its sum is 11.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
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
struct TreeNode* replaceValueInTree(struct TreeNode* root) {
    if (!root) return NULL;

    // Queue for level order traversal
    struct TreeNode** queue = (struct TreeNode**)malloc(100000 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;
        int levelSum = 0;

        // Calculate the sum of values at the current level
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front + i];
            levelSum += node->val;
        }

        // Update each node's value to the sum of its cousins
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front + i];
            int childrenSum = 0;

            if (node->left) {
                childrenSum += node->left->val;
                queue[rear++] = node->left;
            }
            if (node->right) {
                childrenSum += node->right->val;
                queue[rear++] = node->right;
            }

            // Set the value of the current node's children to the sum of cousins
            if (node->left) {
                node->left->val = levelSum - childrenSum;
            }
            if (node->right) {
                node->right->val = levelSum - childrenSum;
            }
        }

        front += levelSize;
    }

    free(queue);
    return root;        
}
