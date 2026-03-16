// Source: https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/   |   Difficulty: Hard
//
// Problem Description:
// We run a preorder depth-first search (DFS) on the root of a binary tree.
//
// At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  If the depth of a node is D, the depth of its immediate child is D + 1.  The depth of the root node is 0.
//
// If a node has only one child, that child is guaranteed to be the left child.
//
// Given the output traversal of this traversal, recover the tree and return its root.
//
// Example:
// Input: traversal = "1-2--3--4-5--6--7"
// Output: [1,2,5,3,4,6,7]
//
// Constraints:
// The number of nodes in the original tree is in the range [1, 1000].
// 	1 <= Node.val <= 109
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* recoverFromPreorder(char* traversal) {
    int len = strlen(traversal);
    int pos = 0;

    struct TreeNode* stack[1000];
    int stackSize = 0;

    while (pos < len) {
        int depth = 0;
        while (pos < len && traversal[pos] == '-') {
            depth++;
            pos++;
        }

        int val = 0;
        while (pos < len && traversal[pos] != '-') {
            val = val * 10 + (traversal[pos] - '0');
            pos++;
        }

        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = val;
        node->left = NULL;
        node->right = NULL;

        while (stackSize > depth) {
            stackSize--;
        }

        if (stackSize > 0) {
            struct TreeNode* parent = stack[stackSize - 1];
            if (parent->left == NULL) {
                parent->left = node;
            } else {
                parent->right = node;
            }
        }

        stack[stackSize++] = node;
    }

    return stack[0];        
}
