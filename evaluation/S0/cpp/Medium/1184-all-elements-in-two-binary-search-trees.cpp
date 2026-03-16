// Source: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.
//
// Example:
// Input: root1 = [2,1,4], root2 = [1,0,3]
// Output: [0,1,1,2,3,4]
//
// Constraints:
// The number of nodes in each tree is in the range [0, 5000].
// 	-105 <= Node.val <= 105
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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> result;
        stack<TreeNode*> stack1, stack2;
        TreeNode* current1 = root1;
        TreeNode* current2 = root2;

        while (current1 || current2 || !stack1.empty() || !stack2.empty()) {
            while (current1) {
                stack1.push(current1);
                current1 = current1->left;
            }
            while (current2) {
                stack2.push(current2);
                current2 = current2->left;
            }

            if (stack2.empty() || (!stack1.empty() && stack1.top()->val <= stack2.top()->val)) {
                current1 = stack1.top();
                stack1.pop();
                result.push_back(current1->val);
                current1 = current1->right;
            } else {
                current2 = stack2.top();
                stack2.pop();
                result.push_back(current2->val);
                current2 = current2->right;
            }
        }

        return result;          
    }
};
