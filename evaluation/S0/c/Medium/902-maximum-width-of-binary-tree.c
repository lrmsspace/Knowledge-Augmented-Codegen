// Source: https://leetcode.com/problems/maximum-width-of-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the maximum width of the given tree.
//
// The maximum width of a tree is the maximum width among all levels.
//
// The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
//
// It is guaranteed that the answer will in the range of a 32-bit signed integer.
//
// Example:
// Input: root = [1,3,2,5,3,null,9]
// Output: 4
// Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3000].
// 	-100 <= Node.val <= 100
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int widthOfBinaryTree(struct TreeNode* root) {
    if (!root) return 0;

    unsigned long long maxWidth = 0;
    unsigned long long queue[3000];
    struct TreeNode* nodes[3000];
    int front = 0, back = 0;

    queue[back] = 0;
    nodes[back++] = root;

    while (front < back) {
        int levelSize = back - front;
        unsigned long long levelMinIndex = queue[front];
        unsigned long long firstIndex = 0, lastIndex = 0;

        for (int i = 0; i < levelSize; i++) {
            unsigned long long index = queue[front] - levelMinIndex;
            struct TreeNode* node = nodes[front++];
            
            if (i == 0) firstIndex = index;
            if (i == levelSize - 1) lastIndex = index;

            if (node->left) {
                queue[back] = index * 2 + 1;
                nodes[back++] = node->left;
            }
            if (node->right) {
                queue[back] = index * 2 + 2;
                nodes[back++] = node->right;
            }
        }

        unsigned long long width = lastIndex - firstIndex + 1;
        if (width > maxWidth) {
            maxWidth = width;
        }
    }

    return (int)maxWidth;       
}
