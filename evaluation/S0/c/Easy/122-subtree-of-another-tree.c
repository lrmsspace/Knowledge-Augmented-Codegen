// Source: https://leetcode.com/problems/subtree-of-another-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
//
// A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
//
// Example:
// Input: root = [3,4,5,1,2], subRoot = [4,1,2]
// Output: true
//
// Constraints:
// The number of nodes in the root tree is in the range [1, 2000].
// 	The number of nodes in the subRoot tree is in the range [1, 1000].
// 	-104 <= root.val <= 104
// 	-104 <= subRoot.val <= 104
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (!root)
        return !subRoot;
    if (!subRoot)
        return true;

    if (root->val == subRoot->val) {
        bool match = true;
        struct TreeNode* r1 = root;
        struct TreeNode* r2 = subRoot;
        struct TreeNode* stack1[2000];
        struct TreeNode* stack2[1000];
        int top1 = -1, top2 = -1;

        while (true) {
            while (r1 && r2) {
                if (r1->val != r2->val) {
                    match = false;
                    break;
                }
                stack1[++top1] = r1;
                stack2[++top2] = r2;
                r1 = r1->left;
                r2 = r2->left;
            }
            if (r1 || r2) {
                match = false;
            }
            if (!match)
                break;
            if (top1 == -1 && top2 == -1)
                break;

            r1 = stack1[top1--];
            r2 = stack2[top2--];
            r1 = r1->right;
            r2 = r2->right;
        }

        if (match)
            return true;
    }

    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);       
}
