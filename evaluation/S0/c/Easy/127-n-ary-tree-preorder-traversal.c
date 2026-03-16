// Source: https://leetcode.com/problems/n-ary-tree-preorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of an n-ary tree, return the preorder traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
//
// Example:
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [1,3,5,6,2,4]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	0 <= Node.val <= 104
// 	The height of the n-ary tree is less than or equal to 1000.
//
//
//  
// Follow up: Recursive solution is trivial, could you do it iteratively?
//

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorder(struct Node* root, int* returnSize) {
    int capacity = 1000;
    int *result = malloc(capacity * sizeof(int));
    *returnSize = 0;

    if (!root) {
        return result;
    }

    struct Node **stack = malloc(capacity * sizeof(struct Node *));
    int stackSize = 0;
    stack[stackSize++] = root;

    while (stackSize > 0) {
        struct Node *node = stack[--stackSize];
        if (*returnSize >= capacity) {
            capacity *= 2;
            result = realloc(result, capacity * sizeof(int));
            stack = realloc(stack, capacity * sizeof(struct Node *));
        }
        result[(*returnSize)++] = node->val;

        for (int i = node->numChildren - 1; i >= 0; i--) {
            stack[stackSize++] = node->children[i];
        }
    }

    free(stack);
    return result;      
}
