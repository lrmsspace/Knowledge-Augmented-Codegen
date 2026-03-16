// Source: https://leetcode.com/problems/merge-bsts-to-create-single-bst/   |   Difficulty: Hard
//
// Problem Description:
// You are given n BST (binary search tree) root nodes for n separate BSTs stored in an array trees (0-indexed). Each BST in trees has at most 3 nodes, and no two roots have the same value. In one operation, you can:
//
//
// 	Select two distinct indices i and j such that the value stored at one of the leaves of trees[i] is equal to the root value of trees[j].
// 	Replace the leaf node in trees[i] with trees[j].
// 	Remove trees[j] from trees.
//
//
// Return the root of the resulting BST if it is possible to form a valid BST after performing n - 1 operations, or null if it is impossible to create a valid BST.
//
// A BST (binary search tree) is a binary tree where each node satisfies the following property:
//
//
// 	Every node in the node's left subtree has a value strictly less than the node's value.
// 	Every node in the node's right subtree has a value strictly greater than the node's value.
//
//
// A leaf is a node that has no children.
//
// Example:
// Input: trees = [[2,1],[3,2,5],[5,4]]
// Output: [3,2,5,1,null,4]
// Explanation:
// In the first operation, pick i=1 and j=0, and merge trees[0] into trees[1].
// Delete trees[0], so trees = [[3,2,5,1],[5,4]].
//
// In the second operation, pick i=0 and j=1, and merge trees[1] into trees[0].
// Delete trees[1], so trees = [[3,2,5,1,null,4]].
//
// The resulting tree, shown above, is a valid BST, so return its root.
//
// Constraints:
// n == trees.length
// 	1 <= n <= 5 * 104
// 	The number of nodes in each tree is in the range [1, 3].
// 	Each node in the input may have children but no grandchildren.
// 	No two roots of trees have the same value.
// 	All the trees in the input are valid BSTs.
// 	1 <= TreeNode.val <= 5 * 104.
//
// Helpful references (internal KB):
// - Strong Orientation (graph, tree, dfs)
//   • When to use: Use this when you need to convert an undirected, bridgeless, and connected graph into a strongly connected directed graph, ensuring reachability between any two vertices.
//   • Idea: This algorithm transforms a bridgeless, connected undirected graph into a strongly connected directed graph by performing a Depth-First Search. It orients DFS tree edges away from the root and back edges towards ancestors, achieving strong connectivity in O(V+E) time.
//   • Invariants: All DFS tree edges discovered so far are oriented from parent to child.; All back edges discovered so far are oriented from child to ancestor.
//   • Tips: Verify the input graph is connected and bridgeless before applying the algorithm.; During DFS, mark visited vertices and track parent-child relationships to distinguish edge types.
//   • Pitfalls: Applying to a graph with bridges will result in a non-strongly connected graph.; Incorrectly identifying or orienting back edges can break the strong connectivity property.
// - Binary Search Trees
//  (tree, enumeration)
//   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
//   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
//   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
//   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode[]} trees
 * @return {TreeNode}
 */
var canMerge = function(trees) {
    const n = trees.length;
    const rootMap = new Map();
    const leafMap = new Map();

    // Map each root value to its tree and count leaf occurrences
    for (const tree of trees) {
        rootMap.set(tree.val, tree);
        if (tree.left) {
            leafMap.set(tree.left.val, (leafMap.get(tree.left.val) || 0) + 1);
        }
        if (tree.right) {
            leafMap.set(tree.right.val, (leafMap.get(tree.right.val) || 0) + 1);
        }
    }

    let mergedRoot = null;

    // Find the unique root that is not a leaf in any other tree
    for (const tree of trees) {
        if (!leafMap.has(tree.val)) {
            if (mergedRoot) return null; // More than one potential root
            mergedRoot = tree;
        }
    }

    if (!mergedRoot) return null; // No unique root found

    // Merge trees using DFS
    const visited = new Set();

    function dfs(node) {
        if (!node) return true;
        if (visited.has(node.val)) return false; // Cycle detected
        visited.add(node.val);

        if (!node.left && rootMap.has(node.val)) {
            node.left = rootMap.get(node.val).left;
            node.right = rootMap.get(node.val).right;
            delete rootMap[node.val]; // Mark as merged
        }

        return dfs(node.left) && dfs(node.right);
    }

    if (!dfs(mergedRoot)) return null; // Invalid merge

    // Check if all trees have been merged
    for (const tree of trees) {
        if (rootMap.has(tree.val)) return null; // Unmerged tree found
    }

    return mergedRoot;
};
