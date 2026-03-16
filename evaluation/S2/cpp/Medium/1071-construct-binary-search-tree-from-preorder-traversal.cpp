// Source: https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.
//
// It is guaranteed that there is always possible to find a binary search tree with the given requirements for the given test cases.
//
// A binary search tree is a binary tree where for every node, any descendant of Node.left has a value strictly less than Node.val, and any descendant of Node.right has a value strictly greater than Node.val.
//
// A preorder traversal of a binary tree displays the value of the node first, then traverses Node.left, then traverses Node.right.
//
// Example:
// Input: preorder = [8,5,1,7,10,12]
// Output: [8,5,10,1,7,null,12]
//
// Constraints:
// 1 <= preorder.length <= 100
// 	1 <= preorder[i] <= 1000
// 	All the values of preorder are unique.
//
// Helpful references (internal KB):
// - Treap (Cartesian tree) (tree, array, divide-and-conquer, recursion)
//   • When to use: Use when a dynamic data structure is needed to support efficient array-like operations (insert, delete, range queries/updates) on an ordered sequence, especially with frequent modifications at arbitrary positions.
//   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on randomly assigned priorities. It supports various dynamic array operations and range queries/updates in expected O(log N) time.
//   • Invariants: For any node, its key is greater than all keys in its left subtree and less than all keys in its right subtree.; For any node, its priority is greater than or equal to the priorities of its children.
//   • Tips: Use random priorities to ensure probabilistic balance, avoiding worst-case O(N) operations.; Implement `split` and `merge` as fundamental building blocks for all other operations.
//   • Pitfalls: Forgetting to push lazy tags before accessing children or performing splits/merges.; Incorrectly updating `cnt` or aggregate fields after tree modifications.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if (preorder.empty()) return nullptr;

        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> st;
        st.push(root);

        for (int i = 1; i < preorder.size(); ++i) {
            TreeNode* node = new TreeNode(preorder[i]);
            if (preorder[i] < st.top()->val) {
                st.top()->left = node;
            } else {
                TreeNode* parent = nullptr;
                while (!st.empty() && preorder[i] > st.top()->val) {
                    parent = st.top();
                    st.pop();
                }
                parent->right = node;
            }
            st.push(node);
        }

        return root;            
    }
};
