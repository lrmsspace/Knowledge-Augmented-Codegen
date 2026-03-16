// Source: https://leetcode.com/problems/n-ary-tree-postorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of an n-ary tree, return the postorder traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
//
// Example:
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [5,6,3,2,4,1]
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
int* postorder(struct Node* root, int* returnSize) {
    int *result = NULL;
    *returnSize = 0;
    if (!root) return result;

    struct Node **stack = malloc(10000 * sizeof(struct Node*));
    int stackSize = 0;

    stack[stackSize++] = root;

    while (stackSize > 0) {
        struct Node *node = stack[--stackSize];

        result = realloc(result, ((*returnSize) + 1) * sizeof(int));
        result[(*returnSize)++] = node->val;

        for (int i = 0; i < node->numChildren; i++) {
            stack[stackSize++] = node->children[i];
        }
    }

    // Reverse the result array
    for (int i = 0; i < (*returnSize) / 2; i++) {
        int temp = result[i];
        result[i] = result[(*returnSize) - 1 - i];
        result[(*returnSize) - 1 - i] = temp;
    }

    free(stack);
    return result;      
}
