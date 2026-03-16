// Source: https://leetcode.com/problems/n-ary-tree-level-order-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given an n-ary tree, return the level order traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
//
// Example:
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [[1],[3,2,4],[5,6]]
//
// Constraints:
// The height of the n-ary tree is less than or equal to 1000
// 	The total number of nodes is between [0, 104]
//

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;

            for (int i = 0; i < levelSize; ++i) {
                Node* currentNode = q.front();
                q.pop();
                currentLevel.push_back(currentNode->val);

                for (Node* child : currentNode->children) {
                    if (child) {
                        q.push(child);
                    }
                }
            }

            result.push_back(currentLevel);
        }

        return result;          
    }
};
