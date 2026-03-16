// Source: https://leetcode.com/problems/most-frequent-subtree-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
//
// The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
//
// Example:
// Input: root = [5,2,-3]
// Output: [2,-3,4]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        unordered_map<int, int> sumCount;
        int maxFreq = 0;

        function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
            if (!node) return 0;
            int leftSum = dfs(node->left);
            int rightSum = dfs(node->right);
            int totalSum = node->val + leftSum + rightSum;
            int freq = ++sumCount[totalSum];
            maxFreq = max(maxFreq, freq);
            return totalSum;
        };

        dfs(root);

        vector<int> result;
        for (const auto& [sum, freq] : sumCount) {
            if (freq == maxFreq) {
                result.push_back(sum);
            }
        }

        return result;          
    }
};
