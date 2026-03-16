// Source: https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given the root of a binary tree with n nodes. Each node is assigned a unique value from 1 to n. You are also given an array queries of size m.
//
// You have to perform m independent queries on the tree where in the ith query you do the following:
//
//
// 	Remove the subtree rooted at the node with the value queries[i] from the tree. It is guaranteed that queries[i] will not be equal to the value of the root.
//
//
// Return an array answer of size m where answer[i] is the height of the tree after performing the ith query.
//
// Note:
//
//
// 	The queries are independent, so the tree returns to its initial state after each query.
// 	The height of a tree is the number of edges in the longest simple path from the root to some node in the tree.
//
// Example:
// Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
// Output: [2]
// Explanation: The diagram above shows the tree after removing the subtree rooted at node with value 4.
// The height of the tree is 2 (The path 1 -> 3 -> 2).
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= n
// 	All the values in the tree are unique.
// 	m == queries.length
// 	1 <= m <= min(n, 104)
// 	1 <= queries[i] <= n
// 	queries[i] != root.val
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
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
 * @param {TreeNode} root
 * @param {number[]} queries
 * @return {number[]}
 */
var treeQueries = function(root, queries) {
    const n = queries.length;
    const height = new Map(); // height of subtree rooted at each node
    const parent = new Map(); // parent of each node
    const depth = new Map(); // depth of each node from root

    // DFS to compute height, parent and depth
    const dfs = (node, par, d) => {
        if (!node) return -1; // height of null is -1
        parent.set(node.val, par);
        depth.set(node.val, d);
        const leftHeight = dfs(node.left, node.val, d + 1);
        const rightHeight = dfs(node.right, node.val, d + 1);
        const h = Math.max(leftHeight, rightHeight) + 1;
        height.set(node.val, h);
        return h;
    };
    
    dfs(root, null, 0);

    const answer = [];
    
    for (const q of queries) {
        let removedHeight = height.get(q); // height of the removed subtree
        let currentNode = q;
        let maxHeightAfterRemoval = 0;

        // Move up the tree to find the maximum height after removal
        while (currentNode !== null) {
            const par = parent.get(currentNode);
            if (par === null) break; // reached root
            
            const siblingHeight = (par.left && par.left.val !== currentNode) ? height.get(par.left.val) : 
                                  (par.right && par.right.val !== currentNode) ? height.get(par.right.val) : -1;
            maxHeightAfterRemoval = Math.max(maxHeightAfterRemoval, siblingHeight + depth.get(par));
            currentNode = par; // move up to the parent
        }
        
        answer.push(maxHeightAfterRemoval);
    }
    
    return answer;
};
