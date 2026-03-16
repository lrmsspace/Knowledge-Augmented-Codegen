// Source: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
//
// You can return the answer in any order.
//
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
// Output: [7,4,1]
// Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 500].
// 	0 <= Node.val <= 500
// 	All the values Node.val are unique.
// 	target is the value of one of the nodes in the tree.
// 	0 <= k <= 1000
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*, TreeNode*> parentMap;
        buildParentMap(root, nullptr, parentMap);

        unordered_set<TreeNode*> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited.insert(target);

        int currentDistance = 0;
        while (!q.empty()) {
            if (currentDistance == k) break;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                for (TreeNode* neighbor : {node->left, node->right, parentMap[node]}) {
                    if (neighbor && visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
            currentDistance++;
        }

        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front()->val);
            q.pop();
        }
        return result;          
    }
};
