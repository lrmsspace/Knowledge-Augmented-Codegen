// Source: https://leetcode.com/problems/k-th-largest-perfect-subtree-size-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and an integer k.
//
// Return an integer denoting the size of the kth largest perfect binary subtree, or -1 if it doesn't exist.
//
// A perfect binary tree is a tree where all leaves are on the same level, and every parent has two children.
//
// Example:
// Input: root = [5,3,6,5,2,5,7,1,8,null,null,6,8], k = 2
//
// Output: 3
//
// Explanation:
//
//
//
// The roots of the perfect binary subtrees are highlighted in black. Their sizes, in non-increasing order are [3, 3, 1, 1, 1, 1, 1, 1].
// The 2nd largest size is 3.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 2000].
// 	1 <= Node.val <= 2000
// 	1 <= k <= 1024
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
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        vector<int> perfectSizes;

        function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
            if (!node) return 0;

            int leftSize = dfs(node->left);
            int rightSize = dfs(node->right);

            if (leftSize == rightSize) {
                int currentSize = leftSize + rightSize + 1;
                perfectSizes.push_back(currentSize);
                return currentSize;
            } else {
                return -1; // Not a perfect subtree
            }
        };

        dfs(root);

        sort(perfectSizes.rbegin(), perfectSizes.rend());

        if (k <= perfectSizes.size()) {
            return perfectSizes[k - 1];
        } else {
            return -1;
        }           
    }
};
