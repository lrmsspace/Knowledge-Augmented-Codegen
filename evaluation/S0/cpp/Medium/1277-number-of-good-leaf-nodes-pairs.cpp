// Source: https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.
//
// Return the number of good leaf node pairs in the tree.
//
// Example:
// Input: root = [1,2,3,null,4], distance = 3
// Output: 1
// Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3. This is the only good pair.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 210].
// 	1 <= Node.val <= 100
// 	1 <= distance <= 10
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
    int countPairs(TreeNode* root, int distance) {
        int result = 0;
        
        function<vector<int>(TreeNode*)> dfs = [&](TreeNode* node) -> vector<int> {
            if (!node) return vector<int>(distance + 1, 0);
            if (!node->left && !node->right) {
                vector<int> leafCount(distance + 1, 0);
                leafCount[1] = 1;
                return leafCount;
            }
            
            vector<int> leftCounts = dfs(node->left);
            vector<int> rightCounts = dfs(node->right);
            
            // Count good pairs between left and right subtrees
            for (int l = 1; l <= distance; ++l) {
                for (int r = 1; r <= distance; ++r) {
                    if (l + r <= distance) {
                        result += leftCounts[l] * rightCounts[r];
                    }
                }
            }
            
            // Prepare counts to return to parent
            vector<int> counts(distance + 1, 0);
            for (int i = 1; i < distance; ++i) {
                counts[i + 1] += leftCounts[i];
                counts[i + 1] += rightCounts[i];
            }
            return counts;
        };
        
        dfs(root);
        return result;          
    }
};
