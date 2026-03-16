// Source: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/   |   Difficulty: Medium
//
// Problem Description:
// You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:
//
//
// struct Node {
//   int val;
//   Node *left;
//   Node *right;
//   Node *next;
// }
//
//
// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
//
// Initially, all next pointers are set to NULL.
//
// Example:
// Input: root = [1,2,3,4,5,6,7]
// Output: [1,#,2,3,#,4,5,6,7,#]
// Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
//
// Constraints:
// The number of nodes in the tree is in the range [0, 212 - 1].
// 	-1000 <= Node.val <= 1000
//
//
//  
// Follow-up:
//
//
// 	You may only use constant extra space.
// 	The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Balanced Search Trees (tree, ds, binary-search, recursion)
//   • When to use: When you need to store a dynamic set of ordered data and require guaranteed logarithmic time complexity for search, insertion, and deletion operations, even in worst-case scenarios.
//   • Idea: Balanced search trees are a class of self-balancing binary search trees that maintain a logarithmic height to ensure O(log N) time complexity for core operations like search, insertion, and deletion. They achieve this balance through structural modifications such as rotations or node splitting/merging.
//   • Invariants: For any node, all keys in its left subtree are less than its key(s), and all keys in its right subtree are greater than its key(s).; The height of the tree is always proportional to log N, ensuring O(log N) operations.
//   • Tips: Understand the specific balancing rules (e.g., AVL rotations, Red-Black tree color properties, 2-3 tree node splits).; Consider the trade-offs between different balanced tree types (e.g., simpler implementation vs. stricter balance).
//   • Pitfalls: Implementation complexity can be high due to intricate rebalancing logic.; Overhead for rebalancing operations might be noticeable for very small N.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/*
// Definition for a Node.
class Node {
    public int val;
    public Node left;
    public Node right;
    public Node next;

    public Node() {}
    
    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, Node _left, Node _right, Node _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/

class Solution {
    public Node connect(Node root) {
        if (root == null) {
            return null;
        }
        
        if (root.left != null) {
            root.left.next = root.right;
        }
        
        if (root.right != null && root.next != null) {
            root.right.next = root.next.left;
        }
        
        connect(root.left);
        connect(root.right);
        
        return root;
    }
}
